/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:44:26 by juchene           #+#    #+#             */
/*   Updated: 2023/03/23 08:01:56 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	*ppx_execute2(t_main *ptr, t_list *cmds, t_cmd	*cmd, t_ext *ext)
{
	int		do_exit;

	if (check_builtin(cmd) && cmd->cmd_array && \
			!ft_strncmp(*cmd->cmd_array, "pwd", ft_strlen(*cmd->cmd_array)))
		ext->exit_status = ft_pwd();
	else if (check_builtin(cmd) && cmd->cmd_array && \
			!ft_strncmp(*cmd->cmd_array, "echo", ft_strlen(*cmd->cmd_array)))
		ext->exit_status = ft_echo(cmds);
	else if (check_builtin(cmd) && cmd->cmd_array && \
			!ft_strncmp(*cmd->cmd_array, "exit", ft_strlen(*cmd->cmd_array)))
		ext->exit_status = ft_exit(cmds, &do_exit, 1);
	else if (check_builtin(cmd) && cmd->cmd_array && \
			!ft_strncmp(*cmd->cmd_array, "env", ft_strlen(*cmd->cmd_array)))
	{
		if (cmd->cmd_array[1])
		{
			ft_error(cmd->cmd_array[1], NO_DIR, 127);
			ext->exit_status = 127;
			return ("");
		}
		ft_array_print_fd(ptr->environ, 1, 1);
		ext->exit_status = 0;
	}
	return ("");
}

void	*ppx_execute(t_main *ptr, t_list *cmds, int *fd, int tmp_fd)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmds->content;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (dup2(tmp_fd, STDIN_FILENO) < 0)
		return (ft_error(NULL, DUP_ERR, 1));
	ppx_close_fd(fd);
	close(tmp_fd);
	if (!check_builtin(cmd) && cmd->cmd_array)
		execve(cmd->path, cmd->cmd_array, ptr->environ);
	else if (check_builtin(cmd) && cmd->cmd_array && \
			!ft_strncmp(*cmd->cmd_array, "cd", ft_strlen(*cmd->cmd_array)))
		get_ext()->exit_status = ft_cd(ptr);
	else if (check_builtin(cmd) && cmd->cmd_array && \
			!ft_strncmp(*cmd->cmd_array, "export", ft_strlen(*cmd->cmd_array)))
		ft_export(ptr, NULL, cmd->cmd_array);
	else if (check_builtin(cmd) && cmd->cmd_array && \
			!ft_strncmp(*cmd->cmd_array, "unset", ft_strlen(*cmd->cmd_array)))
		get_ext()->exit_status = ft_unset(ptr);
	else
		return (ppx_execute2(ptr, cmds, cmds->content, get_ext()));
	return ("");
}

void	*ppx_child_exec(t_main *ptr, t_list *cmds, int *fd, int tmp_fd)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmds->content;
	if (dup2(cmd->outfile, STDOUT_FILENO) < 0)
		return (ft_error(NULL, DUP_ERR, 1));
	ppx_close_fd(fd);
	if (ppx_execute(ptr, cmds, fd, tmp_fd))
		exit(get_ext()->exit_status);
	return ("");
}

void	*ppx_redirect(t_list *cmds, int (*fd)[2], int i)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmds->content;
	if (pipe(*fd) < 0)
		return (ft_error(NULL, PIPE_ERR, 1));
	if (cmd->cmd_array && !ft_strncmp(*cmd->cmd_array, "cd", 2))
	{
		close((*fd)[READ_FD]);
		(*fd)[READ_FD] = dup(cmd->infile);
	}
	if (i != 0)
		cmd->infile = (*fd)[READ_FD];
	if (cmds->next && cmd->outfile == STDOUT_FILENO)
		cmd->outfile = (*fd)[WRITE_FD];
	return ("");
}

void	ppx_fork(t_main *ptr, t_list *cmds, int fd[2], int *tmp_fd)
{
	ptr->pid = fork();
	if (ptr->pid < 0)
	{
		ppx_close_fd(fd);
		close(*tmp_fd);
		ft_error(NULL, FORK_ERR, 1);
	}
	else if (ptr->pid == 0)
		ppx_child_exec(ptr, cmds, fd, *tmp_fd);
	else
	{
		close(*tmp_fd);
		close(fd[WRITE_FD]);
		*tmp_fd = fd[READ_FD];
	}
}
