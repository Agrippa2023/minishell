/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:48:03 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/23 01:52:12 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// a function that recieves a string and a set of characters
// and returns 0 if the string contains only the characters in the set
// and 1 if it contains any other character

int	ft_str_is(char *str, char *set)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (set[j])
		{
			if (str[i] == set[j])
				break ;
			j++;
		}
		if (!set[j])
			return (1);
		i++;
	}
	return (0);
}

// a function to add "" to the part of the string that comes after the = sign

char	*add_quotes(char *str)
{
	int		i;
	char	*temp;

	i = ft_strchri(str, '=');
	temp = ft_substr(str, 0, i + 1);
	temp = ft_strjoin_free(temp, "\"", 1);
	temp = ft_strjoin_free(temp, ft_strrtok(str, '='), 2);
	temp = ft_strjoin_free(temp, "\"", 1);
	return (temp);
}
