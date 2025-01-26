/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 18:18:05 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/23 07:07:26 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	void	*fill_stop(t_list *cmds, char **argv, char **temp)
{
	ft_lstclear(&cmds, free_lst);
	ft_array_free(&argv);
	ft_array_free(&temp);
	return (NULL);
}

static	void	fill_struct(t_cmd **node, char **array[2], int *i)
{
	if (array[0][*i])
	{
		if (array[0][*i][0] == '>' && array[0][*i + 1] && \
					array[0][*i + 1][0] == '>')
			outfile2(node, array[1], i);
		else if (array[0][*i][0] == '>')
			outfile1(node, array[1], i);
		else if (array[0][*i][0] == '<' && array[0][*i + 1] && \
					array[0][*i + 1][0] == '<')
			infile2(node, array[1], i);
		else if (array[0][*i][0] == '<')
			infile1(node, array[1], i);
		else if (array[0][*i][0] != '|')
			(*node)->cmd_array = ft_array_expand((*node)->cmd_array, \
								array[1][*i]);
		else
		{
			ft_error(NULL, PIPE_ENDERR, 2);
			*i = -2;
		}
		return ;
	}
	ft_error(NULL, PIPE_ENDERR, 2);
	*i = -2;
}

t_list	*fill_list(char **argv, int i)
{
	t_list	*cmds[2];
	char	**temp[2];

	cmds[0] = NULL;
	temp[1] = unquote_array(argv);
	while (argv && argv[++i])
	{
		cmds[1] = ft_lstlast(cmds[0]);
		if (i == 0 || (argv[i][0] == '|' && argv[i + 1] && argv[i + 1][0]))
		{
			i += argv[i][0] == '|';
			ft_lstadd_back(&cmds[0], ft_lstnew(init_cmd()));
			cmds[1] = ft_lstlast(cmds[0]);
		}
		temp[0] = argv;
		fill_struct((t_cmd **)&(cmds[1]->content), temp, &i);
		if (i < 0)
			return (fill_stop(cmds[0], argv, temp[1]));
		if (!argv[i])
			break ;
	}
	ft_array_free(&temp[1]);
	ft_array_free(&argv);
	return (cmds[0]);
}
