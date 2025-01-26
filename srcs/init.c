/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 19:55:16 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/20 03:47:38 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_variables(char **argv)
{
	t_main	*ptr;
	char	*temp[2];

	ptr = get_ptr();
	temp[0] = getcwd(NULL, 0);
	ptr->environ = ft_setenv("PWD", temp[0], ptr->environ, 3);
	ft_free(temp[0], NULL);
	temp[0] = ft_getenv("SHLVL", ptr->environ, 5);
	if (!temp[0])
		temp[1] = ft_strdup("1");
	else
		temp[1] = ft_itoa(ft_atoi(temp[0]) + 1);
	ptr->environ = ft_setenv("SHLVL", temp[1], ptr->environ, 5);
	ft_free(temp[0], temp[1]);
	temp[0] = ft_getenv("PATH", ptr->environ, 4);
	if (!temp[0])
		ptr->environ = ft_setenv("PATH", PATH, ptr->environ, 4);
	else
		ft_free(temp[0], NULL);
	temp[0] = ft_getenv("_", ptr->environ, 1);
	if (!temp[0])
		ptr->environ = ft_setenv("_", argv[0], ptr->environ, 1);
	else
		ft_free(temp[0], NULL);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd_array = NULL;
	cmd->infile = STDIN_FILENO;
	cmd->outfile = STDOUT_FILENO;
	cmd->path = NULL;
	return (cmd);
}

t_main	*init_main(char **argv, char **envp)
{
	t_main	*ptr;
	pid_t	pid;

	ptr = get_ptr();
	ptr->argv = argv;
	ptr->cmds = NULL;
	ptr->environ = ft_array_dup(envp);
	pid = fork();
	if (pid < 0)
	{
		ft_error(NULL, FORK_ERR, 1);
		ft_array_free(&ptr->environ);
		exit(1);
	}
	if (pid == 0)
	{
		ft_array_free(&ptr->environ);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	ptr->pid = pid - 1;
	init_variables(argv);
	return (ptr);
}
