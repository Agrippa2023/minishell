/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   per_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 01:58:02 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/23 02:07:23 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_history(t_main *ptr)
{
	char	*cmd;
	int		fd;
	char	*temp;

	temp = ft_getenv("HOME", ptr->environ, 4);
	if (temp)
	{
		temp = ft_strjoin_free(temp, "/.minishell_history", 1);
		fd = open(temp, O_CREAT | O_RDWR | O_APPEND, 0666);
		cmd = get_next_line(fd);
		while (cmd)
		{
			cmd = ft_substr_free(cmd, 0, ft_strchri(cmd, '\n'), 1);
			add_history(cmd);
			ft_free(cmd, NULL);
			cmd = get_next_line(fd);
		}
		close(fd);
		ft_free(temp, NULL);
	}
}

void	add_to_history(t_main *ptr, char *line)
{
	int		fd;
	char	*temp;

	if (line[0] != '\0')
	{
		add_history(line);
		temp = ft_getenv("HOME", ptr->environ, 4);
		if (temp)
		{
			temp = ft_strjoin_free(temp, "/.minishell_history", 1);
			fd = open(temp, O_CREAT | O_RDWR | O_APPEND, 0666);
			ft_putendl_fd(line, fd);
			close(fd);
			ft_free(temp, NULL);
		}
	}
}
