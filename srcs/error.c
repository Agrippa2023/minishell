/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 20:26:05 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/20 04:18:14 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	errors2(int error)
{
	if (error == FORK_ERR)
		ft_putstr_fd(": fork failed", STDERR_FILENO);
	else if (error == PIPE_ERR)
		ft_putstr_fd(": error while creating pipe", STDERR_FILENO);
	else if (error == PIPE_ENDERR)
		ft_putstr_fd(": syntax error near unexpected token `|'", STDERR_FILENO);
	else if (error == MEM)
		ft_putstr_fd(": no memory left on device", STDERR_FILENO);
	else if (error == REDIR_ERR)
		ft_putstr_fd(": syntax error near unexpected token `>'", STDERR_FILENO);
	else if (error == REDIR_ERR2)
		ft_putstr_fd(": syntax error near unexpected token `<'", STDERR_FILENO);
}

static void	errors(int error)
{
	if (error == NO_DIR)
		ft_putstr_fd(": No such file or directory", STDERR_FILENO);
	else if (error == IS_DIR)
		ft_putstr_fd(": Is a directory", STDERR_FILENO);
	else if (error == NOT_DIR)
		ft_putstr_fd(": Not a directory", STDERR_FILENO);
	else if (error == NO_CMD)
		ft_putstr_fd(": command not found", STDERR_FILENO);
	else if (error == NO_PERM)
		ft_putstr_fd(": permission denied", STDERR_FILENO);
	else if (error == QUOTE)
		ft_putstr_fd(": no matching quote found", STDERR_FILENO);
	else if (error == DUP_ERR)
		ft_putstr_fd(": dup2 failed", STDERR_FILENO);
	else
		errors2(error);
}

void	*ft_error(char *arg, int error, int rno)
{
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd("Minishell: Error! ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	errors(error);
	ft_putendl_fd(BLANK, STDERR_FILENO);
	get_ext()->exit_status = rno;
	return (NULL);
}
