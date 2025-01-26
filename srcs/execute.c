/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 03:50:42 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/23 10:56:20 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*check_path(char *cmd, char *path, char **paths)
{
	int		i;
	char	*temp;

	i = -1;
	path = NULL;
	while (paths && paths[++i])
	{
		ft_free(path, NULL);
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (NULL);
		path = ft_strjoin_free(temp, cmd, 1);
		if (!access(path, F_OK))
			return (path);
	}
	if (path)
		ft_free(path, NULL);
	return (NULL);
}

static	DIR	*check_cmd(t_main *ptr, t_list *cmds, char ***array, char *path)
{
	DIR		*dir;
	t_cmd	*cmd;

	dir = NULL;
	cmd = cmds->content;
	if (cmd && cmd->cmd_array)
		dir = opendir(*cmd->cmd_array);
	if (cmd && cmd->cmd_array && ft_strchr(*cmd->cmd_array, '/') && !dir)
	{
		*array = ft_split(*cmd->cmd_array, '/');
		cmd->path = ft_strdup(*cmd->cmd_array);
		ft_free(cmd->cmd_array[0], NULL);
		cmd->cmd_array[0] = ft_strdup(array[0][ft_array_size(*array) - 1]);
	}
	else if (cmd && cmd->cmd_array && !check_builtin(cmd) && !dir)
	{
		path = ft_getenv("PATH", ptr->environ, 4);
		*array = ft_split(path, ':');
		ft_free(path, NULL);
		cmd->path = check_path(*cmd->cmd_array, cmd->path, *array);
		if (!cmd->path || !cmd->cmd_array[0] || !cmd->cmd_array[0][0])
			ft_error(*cmd->cmd_array, NO_CMD, 127);
	}
	return (dir);
}

void	get_cmd(t_main *ptr, t_list *cmds, char **array, char *path)
{
	DIR		*dir;
	t_cmd	*cmd;

	cmd = cmds->content;
	dir = check_cmd(ptr, cmds, &array, path);
	if (!check_builtin(cmd) && cmd && cmd->cmd_array && dir)
		ft_error(*cmd->cmd_array, IS_DIR, 127);
	else if (!check_builtin(cmd) && cmd && cmd->path && \
			access(cmd->path, F_OK) == -1)
		ft_error(cmd->path, NO_DIR, 127);
	else if (!check_builtin(cmd) && cmd && cmd->path && \
			access(cmd->path, X_OK) == -1)
		ft_error(cmd->path, NO_PERM, 126);
	if (dir)
		closedir(dir);
	ft_array_free(&array);
}

void	ft_pipex(t_list *cmds, t_cmd *cmd, int *tmp, int i)
{
	t_main	*ptr;
	int		fd[2];
	DIR		*dir;

	ptr = get_ptr();
	dir = NULL;
	ppx_redirect(cmds, &fd, i);
	if (cmd->cmd_array)
		dir = opendir(*cmd->cmd_array);
	if ((cmd->cmd_array && cmd->path && \
		access(cmd->path, X_OK) == 0) || check_builtin(cmd))
		ppx_fork(ptr, cmds, fd, tmp);
	else if (!check_builtin(cmd) && ((cmd->path && !access(cmd->path, F_OK))
			|| dir))
		get_ext()->exit_status = 126;
	else if (!check_builtin(cmd) && cmd->cmd_array)
		get_ext()->exit_status = 127;
	if (dir)
		closedir(dir);
}

void	execute(t_main *ptr, t_list *cmds, t_cmd *cmd, int i)
{
	int		tmp[2];

	tmp[0] = dup(cmd->infile);
	while (cmds && cmd)
	{
		cmd = (t_cmd *)cmds->content;
		get_cmd(ptr, cmds, NULL, NULL);
		ft_pipex(cmds, cmd, &tmp[0], i);
		cmds = cmds->next;
		i++;
	}
	close(tmp[0]);
	tmp[1] = 0;
	while (i-- > 0)
	{
		if (tmp[1]++ == 0)
			tmp[0] = waitpid(ptr->pid, &(get_ext()->exit_status), 0);
		else
			waitpid(-1, 0, 0);
	}
	if (i == 0)
		get_ext()->exit_status = (((get_ext()->exit_status) & 0xff00) >> 8);
}
