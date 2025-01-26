/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:46:13 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/23 03:43:07 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_export_error(char *str, int i[2])
{
	char	*temp_str;

	temp_str = ft_strjoin("export: '", str);
	temp_str = ft_strjoin_free(temp_str, "': not a valid identifier", 1);
	ft_error(temp_str, 0, i[2]);
	ft_free(temp_str, NULL);
}

static void	ft_export_print(t_main *ptr)
{
	int		i;
	char	**temp;
	char	*temp_str;

	i = 0;
	temp = ft_array_sort(ptr->environ);
	while (temp[i])
	{
		temp_str = ft_strdup("declare -x ");
		temp_str = ft_strjoin_free(temp_str, add_quotes(temp[i]), 2);
		ft_putendl_fd(temp_str, 1);
		ft_free(temp_str, NULL);
		i++;
	}
	ft_array_free(&temp);
}

static void	ft_add_2(char *temp_str, int pos[2], int i[3])
{
	t_main	*ptr;

	ptr = get_ptr();
	pos[0] = var_in_envp(ptr->environ, temp_str, i);
	if (pos[0] == 1)
	{
		if (pos[1] == 1)
			temp_str = ft_strjoin_free(ptr->environ[i[1]], \
										ft_strrtok(temp_str, '='), 2);
		else
			ft_free(ptr->environ[i[1]], NULL);
		ptr->environ[i[1]] = ft_strdup(temp_str);
	}
	else if (!pos[0] && ft_strlen(temp_str) > 0)
		ptr->environ = ft_array_expand(ptr->environ, temp_str);
	else if (!pos[0] && ft_strlen(temp_str) == 0)
	{
		ft_error("export: `' not a valid identifier", 0, 1);
		i[2] = 1;
	}
	if (pos[1] == 1)
		ft_free(temp_str, NULL);
}

static void	ft_add_variable(char **cmd, char *temp_str, int pos[2], int i[3])
{
	i[0] = 1;
	while (cmd[i[0]])
	{
		i[2] = ft_export_variable_check(cmd[i[0]]);
		if (!i[2])
		{
			pos[1] = 0;
			if (ft_strchr(cmd[i[0]], '+'))
			{
				temp_str = ft_strjoin_free(ft_strtok(cmd[i[0]], '+'), \
								ft_strrtok(cmd[i[0]], '+'), 2);
				pos[1] = 1;
			}
			else
				temp_str = cmd[i[0]];
			ft_add_2(temp_str, pos, i);
		}
		else
			ft_export_error(cmd[i[0]], i);
		i[0]++;
	}
}

void	ft_export(t_main *ptr, char *temp_str, char **cmd)
{
	int		i[3];
	int		pos[2];

	i[2] = 0;
	if (ft_array_size(cmd) >= 2)
		ft_add_variable(cmd, temp_str, pos, i);
	else
		ft_export_print(ptr);
	if (i[2] != 0)
		get_ext()->exit_status = i[2];
}
