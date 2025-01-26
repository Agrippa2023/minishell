/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 19:36:16 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/22 23:09:40 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_ext	*get_ext(void)
{
	static t_ext	*ext = NULL;

	if (ext == NULL)
	{
		ext = (t_ext *)malloc(sizeof(t_ext));
		ft_memset(ext, 0, 1);
		ext->exit_status = 0;
		if (!ext)
			return (NULL);
	}
	return (ext);
}

t_main	*get_ptr(void)
{
	static t_main	*ptr = NULL;

	if (ptr == NULL)
	{
		ptr = (t_main *)malloc(sizeof(t_main));
		if (!ptr)
			return (NULL);
		ptr->cmds = NULL;
		ptr->environ = NULL;
		ptr->pid = 0;
		ptr->argv = NULL;
	}
	return (ptr);
}
