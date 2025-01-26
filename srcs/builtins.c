/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 15:44:20 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/23 09:15:40 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_builtin(t_cmd *cmd)
{
	int			i;
	size_t		z;
	static char	tab[7][7] = {{"echo"}, {"exit"}, {"cd"}, {"export"},
	{"unset"}, {"env"}, {"pwd"}};

	i = -1;
	if (!cmd || cmd->cmd_array == NULL)
		return (0);
	if ((cmd->cmd_array && ft_strchr(*cmd->cmd_array, '/'))
		|| (cmd->path && ft_strchr(cmd->path, '/')))
		return (0);
	while (++i < 7)
	{
		z = ft_strlen(*cmd->cmd_array);
		if (ft_strlen(tab[i]) > z)
			z = ft_strlen(tab[i]);
		if (ft_strncmp(tab[i], *cmd->cmd_array, z) == 0)
			return (1);
	}
	return (0);
}

int	ft_echo(t_list	*cmd)
{
	int		i[2];
	int		nwline;
	char	**argv;

	i[0] = 0;
	i[1] = 0;
	nwline = 1;
	argv = ((t_cmd *)cmd->content)->cmd_array;
	while (argv && argv[++i[0]])
	{
		if (!i[1] && !ft_strncmp(argv[i[0]], "-n", 2)
			&& (ft_countchar(argv[i[0]], 'n')
				== (int)(ft_strlen(argv[i[0]]) - 1)))
			nwline = 0;
		else
		{
			i[1] = 1;
			ft_putstr_fd(argv[i[0]], 1);
			if (argv[i[0] + 1])
				ft_putchar_fd(' ', 1);
		}
	}
	return (write(1, "\n", nwline) == 2);
}

int	ft_pwd(void)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	ft_putendl_fd(temp, 1);
	ft_free(temp, NULL);
	return (0);
}

int	builtin(t_main *ptr, t_list *cmds, int *do_exit, int n)
{
	char	**array;
	t_ext	*ext;

	array = ((t_cmd *)cmds->content)->cmd_array;
	n = 0;
	ext = get_ext();
	if (array)
		n = ft_strlen(*array);
	if (!cmds->next && array && !ft_strncmp(*array, "exit", n) && n == 4)
		ext->exit_status = ft_exit(cmds, do_exit, 0);
	else if (!cmds->next && array && !ft_strncmp(*array, "cd", n) && n == 2)
		ext->exit_status = ft_cd(ptr);
	else if (!cmds->next && array && !ft_strncmp(*array, "export", n) && n == 6)
		ft_export(ptr, NULL, array);
	else if (!cmds->next && array && !ft_strncmp(*array, "unset", n) && n == 5)
		ext->exit_status = ft_unset(ptr);
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		execute(ptr, cmds, cmds->content, 0);
	}
	return (ext->exit_status);
}
