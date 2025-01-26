/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 19:02:14 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/23 01:38:57 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*read_heredoc(char *str[2], size_t len, char *limit, char *warn)
{
	char	*temp_str;

	temp_str = NULL;
	while (get_ext()->exit_status != 130 && (!str[0] || \
		ft_strncmp(str[0], limit, len) || ft_strlen(limit) != len))
	{
		signal(SIGINT, signal_handler);
		if (get_ext()->exit_status == 130)
			break ;
		str[1] = ft_strjoin_free(str[1], str[0], 2);
		str[0] = readline("heredoc> ");
		if (!str[0])
		{
			printf("%s (wanted `%s\')\n", warn, limit);
			break ;
		}
		temp_str = str[0];
		str[0] = expand_variables(str[0], -1, get_ptr());
		if (temp_str != str[0])
			ft_free(temp_str, NULL);
		str[0] = ft_strjoin_free(str[0], "\n", 1);
		len = ft_strlen(str[0]) - 1;
	}
	ft_free(str[0], NULL);
	return (str[1]);
}

int	get_heredoc(char *str[2], char *temp[2])
{
	int		fd[2];
	t_ext	*ext;

	ext = get_ext();
	ext->exit_status = 0;
	if (pipe(fd) == -1)
	{
		ft_error(NULL, PIPE_ERR, 1);
		return (-1);
	}
	str[1] = read_heredoc(str, 0, temp[0], temp[1]);
	write(fd[WRITE_FD], str[1], ft_strlen(str[1]));
	close(fd[WRITE_FD]);
	ft_free(str[1], NULL);
	if (ext->exit_status == 130)
	{
		close(fd[READ_FD]);
		return (-1);
	}
	return (fd[READ_FD]);
}
