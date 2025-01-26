/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 14:19:17 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/23 03:44:39 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	expand_variables_2(char *str, int z, char **f_str, t_main *ptr)
{
	char	*temp[2];

	if (str[0] == '$' && z > 1 && (!is_valid_char(str[1]) || \
		str[1] == '$' || str[1] == '?' || str[1] == '0'))
	{
		if (z == 2 && (str[1] == '?' || str[1] == '$' || str[1] == '0'))
		{
			if (str[1] == '?')
				temp[0] = ft_itoa(get_ext()->exit_status);
			else if (str[1] == '$')
				temp[0] = ft_itoa(ptr->pid);
			else if (str[1] == '0')
				temp[0] = ft_strdup(ptr->argv[0]);
		}
		else
		{
			temp[1] = ft_substr(str, 1, z);
			temp[0] = ft_getenv(temp[1], ptr->environ, ft_strlen(temp[1]));
			ft_free(temp[1], NULL);
		}
		if (temp[0])
			*f_str = ft_strjoin_free(*f_str, temp[0], 2);
	}
	else
		*f_str = ft_strjoin_free(*f_str, str, 1);
}

char	*expand_variables(char *str, int i, t_main *ptr)
{
	char	**tb;
	char	*temp_str[2];
	int		z;

	z = 0;
	temp_str[0] = NULL;
	temp_str[1] = NULL;
	tb = ft_split_keep(str, '$');
	while (tb[++i])
	{
		z = ft_strlen(tb[i]);
		if (tb[i][0] == '$' && z > 1 && (tb[i][1] == '\'' || tb[i][1] == '\"'))
		{
			temp_str[0] = ft_substr(tb[i], 1, z);
			if (ft_str_is(temp_str[0], "\'\"") != 0)
				temp_str[1] = ft_strjoin_free(temp_str[1], temp_str[0], 1);
			else
				temp_str[1] = ft_strjoin_free(temp_str[1], tb[i], 1);
			ft_free(temp_str[0], NULL);
		}
		else
			expand_variables_2(tb[i], z, &temp_str[1], ptr);
	}
	ft_array_free(&tb);
	return (temp_str[1]);
}

char	*expand_path(char *str, int i, int quotes[2], char *var)
{
	char	*path;
	char	*temp;

	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
		if (!quotes[0] && !quotes[1] && str[i] == '~'
			&& (((i == 0 && str[i + 1] == '/') || (i == 0 && !str[i + 1]))))
		{
			path = ft_substr(str, 0, i);
			path = ft_strjoin_free(path, var, 1);
			temp = ft_substr(str, i + 1, ft_strlen(str));
			ft_free(str, NULL);
			str = ft_strjoin_free(path, temp, 2);
			return (expand_path(str, i + ft_strlen(var) - 1, quotes, var));
		}
	}
	ft_free(var, NULL);
	return (str);
}
