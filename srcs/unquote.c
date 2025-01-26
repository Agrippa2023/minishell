/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 18:47:59 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/20 03:49:24 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	int	unquote_size(char *str, int squote, int dquote)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str && str[i])
	{
		squote = (squote + (!dquote && str[i] == '\'')) % 2;
		dquote = (dquote + (!squote && str[i] == '\"')) % 2;
		if ((str[i] == '\"' && !squote) || (str[i] == '\'' && !dquote))
			size++;
		i++;
	}
	if (squote || dquote)
		return (-1);
	return (size);
}

static char	*unquote_str(char *str, int squote, int dquote)
{
	int		i[2];
	int		size;
	char	*nwstr;

	i[0] = 0;
	i[1] = -1;
	size = unquote_size(str, 0, 0);
	if (!str || size == -1)
		return (NULL);
	nwstr = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1 - size));
	if (!nwstr)
		return (NULL);
	while (str[i[0]])
	{
		squote = (squote + (!dquote && str[i[0]] == '\'')) % 2;
		dquote = (dquote + (!squote && str[i[0]] == '\"')) % 2;
		if ((str[i[0]] != '\"' || squote) && (str[i[0]] != '\'' || dquote) \
			&& ++i[1] >= 0)
			nwstr[i[1]] = str[i[0]];
		i[0]++;
	}
	nwstr[++i[1]] = '\0';
	return (nwstr);
}

char	**unquote_array(char **argv)
{
	char	**nwarray;
	char	*temp;
	int		i[2];

	i[0] = 0;
	nwarray = ft_array_dup(argv);
	i[1] = ft_array_size(nwarray);
	while (i[1] > 1 && nwarray && nwarray[++i[0]])
	{
		temp = unquote_str(nwarray[i[0]], 0, 0);
		ft_free(nwarray[i[0]], NULL);
		nwarray[i[0]] = temp;
	}
	return (nwarray);
}
