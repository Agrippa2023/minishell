/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 03:50:15 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/23 01:43:47 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_export_variable_check(char *variable)
{
	int	i;
	int	z;

	i = 0;
	if (variable[i] == '=' || ft_isdigit(variable[i]))
		return (1);
	while (variable[i] && variable[i] != '=')
	{
		if (variable[i] == '+' && variable[i + 1] && variable[i + 1] != '=')
			return (1);
		z = is_valid_char(variable[i]);
		if (z == 2 && i == 0)
			return (2);
		else if (z == 1 || z == 2)
			return (1);
		i++;
	}
	return (0);
}

int	is_valid_var(char *var)
{
	int		i;
	char	*set;

	set = " \t\n\v\f\r=+*/-!@#$%^&*(){}[]|\\;:'\",.<>?~";
	i = 0;
	if (!var)
		return (-1);
	if (var[i] != '_' && !ft_isalpha(var[i]))
		return (i);
	return (ft_strchri_set(var, set));
}

int	is_valid_char(char c)
{
	int		i;
	char	*set;

	i = 0;
	set = " \t\n\v\f\r=*/-!@#$%^&*(){}[]|\\;:'\",.<>?~";
	while (set[i])
	{
		if (c == set[i])
		{
			if (c == '-')
				return (2);
			else
				return (1);
		}
		i++;
	}
	return (0);
}
