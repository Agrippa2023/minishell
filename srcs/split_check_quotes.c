/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_check_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:50:04 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/21 02:55:02 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	int	count_words(char *line, char *set, int i[2])
{
	int	quote[2];

	quote[0] = 0;
	quote[1] = 0;
	while (line[i[0]])
	{
		if (!ft_strchr(set, line[i[0]]))
		{
			i[1]++;
			while ((!ft_strchr(set, line[i[0]]) || quote[0]) && line[i[0]])
			{
				if (!quote[1] && (line[i[0]] == '\"' || line[i[0]] == '\''))
					quote[1] = line[i[0]];
				quote[0] = (quote[0] + (line[i[0]] == quote[1])) % 2;
				quote[1] *= quote[0] != 0;
				i[0]++;
			}
			if (quote[0])
				return (-1);
		}
		else
			i[0]++;
	}
	return (i[1]);
}

static	char	**fill_array(char **array, char *line, char *set, int i[3])
{
	int	quote[2];
	int	line_len;

	quote[0] = 0;
	quote[1] = 0;
	line_len = ft_strlen(line);
	while (line[i[0]])
	{
		while (ft_strchr(set, line[i[0]]) && line[i[0]])
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(set, line[i[0]]) || quote[0] || quote[1])
			&& line[i[0]])
		{
			quote[0] = (quote[0] + (!quote[1] && line[i[0]] == '\'')) % 2;
			quote[1] = (quote[1] + (!quote[0] && line[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= line_len)
			array[i[2]++] = "\0";
		else
			array[i[2]++] = ft_substr(line, i[1], i[0] - i[1]);
	}
	return (array);
}

char	**split_and_check_quotes(char *line, char *set)
{
	char	**cmd_array;
	int		word_count;
	int		i[3];
	int		z[2];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	z[0] = 0;
	z[1] = 0;
	if (!line)
		return (NULL);
	word_count = count_words(line, set, z);
	if (word_count == -1)
		return (NULL);
	cmd_array = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!cmd_array)
		return (NULL);
	cmd_array = fill_array(cmd_array, line, set, i);
	cmd_array[word_count] = NULL;
	return (cmd_array);
}
