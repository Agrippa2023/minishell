/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:09:11 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/22 23:50:13 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_is_redir(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

static int	ft_left_redir(char *str, int *i)
{
	if (!str[*i] || ft_is_redir(str[*i]))
	{
		if (str[*i] && str[*i] == '>')
			ft_error(NULL, REDIR_ERR, 2);
		else
			ft_error("syntax error near unexpected token `newline'", 0, 2);
		return (-1);
	}
	if (str[*i] == ' ')
	{
		while (str[*i] && ft_isspace(str[*i]))
			(*i)++;
		if (str[*i] == '<' || str[*i] == '>')
		{
			if (str[*i] == '<')
				ft_error(NULL, REDIR_ERR2, 2);
			else
				ft_error(NULL, REDIR_ERR, 2);
			return (-1);
		}
	}
	return (0);
}

static int	ft_right_redir(char *str, int *i)
{	
	if (!str[*i] || ft_is_redir(str[*i]))
	{
		if (str[*i] && str[*i] == '>')
			ft_error(NULL, REDIR_ERR, 2);
		else if (str[*i] && str[*i] == '<')
			ft_error(NULL, REDIR_ERR2, 2);
		else if (!str[*i])
			ft_error("syntax error near unexpected token `newline'", 0, 2);
		return (-1);
	}
	if (str[*i] == ' ')
	{
		while (str[*i] && ft_isspace(str[*i]))
			(*i)++;
		if (str[*i] == '<' || str[*i] == '>')
		{
			if (str[*i] == '<')
				ft_error(NULL, REDIR_ERR2, 2);
			else
				ft_error(NULL, REDIR_ERR, 2);
			return (-1);
		}
	}
	return (0);
}
// a function to evaluate how many '<' or '>' are in a string

int	ft_count_redir(char *str, int i)
{
	while (str[i])
	{
		if (ft_is_redir(str[i]))
		{
			if (str[i] == '<')
			{
				if (str[++i] && str[i] == '<')
					i++;
				if (str[i] && ft_left_redir(str, &i) == -1)
					return (-1);
			}
			if (str[i] == '>')
			{
				if (str[++i] && str[i] == '>')
					i++;
				if (str[i] && ft_right_redir(str, &i) == -1)
					return (-1);
			}
		}
		if (str[i])
			i++;
	}
	return (0);
}
