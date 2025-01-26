/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_keep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:05:29 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/23 03:13:04 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_word_len_2(char *str, char c, int i)
{
	int	j;

	if (is_valid_char(str[i]))
	{
		j = i;
		while (str[j] && str[j] == '\"')
			j++;
		if (j % 2 != 0)
			while (str[i] && is_valid_char(str[i]) && str[i] != c)
				i++;
		else
			while (str[i] && is_valid_char(str[i]) && \
					str[i] != c && str[i] != '\'')
				i++;
	}
	else if (!is_valid_char(str[i]))
	{
		if (i > 0 && str[i - 1] == c && ft_isdigit(str[i]))
			i++;
		else
			while (str[i] && str[i] != c && !is_valid_char(str[i]))
				i++;
	}
	return (i);
}

static int	ft_word_len(char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == c)
	{
		i++;
		if (str[i] && str[i] == c)
			return (i + 1);
	}
	if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\0' && str[i] != '\'')
			i++;
		if (str[i] != '\0')
			i++;
	}
	i = ft_word_len_2(str, c, i);
	return (i);
}

static int	ft_count_words_2(char *str, char c, int i)
{
	int		j;

	if (is_valid_char(str[i]))
	{
		j = i;
		while (str [j] && str[j] == '\"')
			j++;
		if (j % 2 != 0)
			while (str[i] && is_valid_char(str[i]) && str[i] != c)
				i++;
		else
			while (str[i] && is_valid_char(str[i]) && \
					str[i] != c && str[i] != '\'')
				i++;
	}
	else if (!is_valid_char(str[i]))
	{
		if (i > 0 && str[i - 1] == c && ft_isdigit(str[i]))
			i++;
		else
			while (str[i] && str[i] != c && !is_valid_char(str[i]))
				i++;
	}
	return (i);
}

static int	ft_count_words(char *str, char c)
{
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	while (str[i[0]])
	{
		i[1]++;
		if (str[i[0]] == c)
		{
			i[0]++;
			if (str[i[0]] && str[i[0]] == c)
				i[0]++;
		}
		if (str[i[0]] == '\'')
		{
			i[0]++;
			while (str[i[0]] != '\0' && str[i[0]] != '\'')
				i[0]++;
			if (str[i[0]] != '\0')
				i[0]++;
		}
		i[0] = ft_count_words_2(str, c, i[0]);
	}
	return (i[1]);
}

char	**ft_split_keep(char *s, char c)
{
	int		i;
	int		z;
	int		size;
	char	**tab;
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)s;
	i = -1;
	size = ft_count_words(str, c);
	tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	while (++i < size)
	{
		z = ft_word_len(str, c);
		tab[i] = ft_strcpy_non_static(str, z);
		str += z;
	}
	tab[size] = 0;
	ft_free(s, NULL);
	return (tab);
}
