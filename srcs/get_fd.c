/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 18:41:49 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/22 23:46:45 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	outfile2(t_cmd **node, char **argv, int *i)
{
	char	*error;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 1;
	error = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (argv[++(*i)])
		(*node)->outfile = get_fd((*node)->outfile, argv[*i], flags);
	if (!argv[*i] || (*node)->outfile == -1)
	{
		*i = -1;
		if ((*node)->outfile != -1)
			ft_error(error, 0, 2);
		else
			get_ext()->exit_status = 1;
	}
}

void	outfile1(t_cmd **node, char **argv, int *i)
{
	char	*error;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 0;
	error = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (argv[*i])
		(*node)->outfile = get_fd((*node)->outfile, argv[*i], flags);
	if (!argv[*i] || (*node)->outfile == -1)
	{
		*i = -1;
		if ((*node)->outfile != -1)
			ft_error(error, 0, 2);
		else
			get_ext()->exit_status = 1;
	}
}

void	infile2(t_cmd **node, char **argv, int *i)
{
	char	*temp[2];
	char	*str[2];

	temp[1] = "minishell: warning: here-document delimited by end-of-file";
	temp[0] = NULL;
	str[0] = NULL;
	str[1] = NULL;
	(*i)++;
	if (argv[++(*i)] && argv[*i][0] != '<')
	{
		temp[0] = argv[*i];
		(*node)->infile = get_heredoc(str, temp);
	}
	if (!argv[*i] || (*node)->infile == -1)
	{
		*i = -1;
		if ((*node)->infile != -1)
			ft_error(ERROR1, 0, 2);
		else
			get_ext()->exit_status = 1;
	}
}

void	infile1(t_cmd **node, char **argv, int *i)
{
	int		flags[2];
	char	*error;

	flags[0] = 0;
	flags[1] = 0;
	error = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (argv[*i])
		(*node)->infile = get_fd((*node)->infile, argv[*i], flags);
	if (!argv[*i] || (*node)->infile == -1)
	{
		*i = -1;
		if ((*node)->infile != -1)
			ft_error(error, 0, 2);
		else
			get_ext()->exit_status = 1;
	}
}

int	get_fd(int oldfd, char *path, int flags[2])
{
	int	nwfd;

	if (!path)
		return (-1);
	if (oldfd > STDERR_FILENO)
		close(oldfd);
	if (access(path, F_OK) == -1 && !flags[0])
		ft_error(path, NO_DIR, 127);
	else if (!flags[0] && access(path, R_OK) == -1)
		ft_error(path, NO_PERM, 126);
	else if (flags[0] && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		ft_error(path, NO_PERM, 126);
	if (flags[0] && flags[1])
		nwfd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (flags[0] && !flags[1])
		nwfd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!flags[0] && oldfd != -1)
		nwfd = open(path, O_RDONLY);
	else
		nwfd = oldfd;
	return (nwfd);
}
