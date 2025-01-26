/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 18:52:24 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/20 05:39:45 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_lst(void *content)
{
	t_cmd	*node;

	node = content;
	ft_array_free(&node->cmd_array);
	ft_free(node->path, NULL);
	if (node->infile > STDERR_FILENO)
		close(node->infile);
	if (node->outfile > STDERR_FILENO)
		close(node->outfile);
	ft_free(node, NULL);
}

void	free_ptr(void)
{
	t_main	*ptr;

	ptr = get_ptr();
	ft_array_free(&ptr->environ);
	ft_lstclear(&ptr->cmds, free_lst);
	ft_free(ptr, NULL);
}

// a function to free two void pointer and set it to NULL

int	ft_free(void *ptr, void *ptr2)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	if (ptr2)
	{
		free(ptr2);
		ptr2 = NULL;
	}
	return (1);
}

void	ppx_close_fd(int fd[2])
{
	close(fd[READ_FD]);
	close(fd[WRITE_FD]);
}
