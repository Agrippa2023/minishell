/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 06:10:00 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/23 01:34:39 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*search_envp(char *var, char **envp, char *temp, int z)
{
	int		i;
	size_t	j;
	int		zz;

	i = -1;
	while (!ft_strchr(temp, '=') && envp && envp[++i])
	{
		zz = z;
		if (zz < ft_strchri(envp[i], '='))
			zz = ft_strchri(envp[i], '=');
		if (!ft_strncmp(envp[i], temp, zz))
		{
			j = ft_strlen(temp);
			ft_free(temp, NULL);
			if (ft_strlen(var) == j)
				return (ft_substr(envp[i], zz + 1, ft_strlen(envp[i])));
			else
			{
				temp = ft_substr(envp[i], zz + 1, ft_strlen(envp[i]));
				return (ft_strjoin_free(temp, var + j, 1));
			}
		}
	}
	ft_free(temp, NULL);
	return (NULL);
}

char	*ft_getenv(char *var, char **envp, int z)
{
	int		j;
	char	*temp;

	j = is_valid_var(var);
	if (j != -1)
		temp = ft_substr(var, 0, j);
	else
		temp = ft_strdup(var);
	if (z < 0 || j != -1)
		z = ft_strlen(temp);
	return (search_envp(var, envp, temp, z));
}

int	var_in_envp(char **envp, char *var, int i[2])
{
	size_t	len;
	char	*temp[2];

	i[1] = -1;
	if (ft_strchri(var, '=') != -1)
		temp[0] = ft_strtok(var, '=');
	else
		temp[0] = ft_strdup(var);
	len = ft_strlen(temp[0]);
	while (envp[++i[1]])
	{
		if (ft_strchri(envp[i[1]], '=') != -1)
			temp[1] = ft_strtok(envp[i[1]], '=');
		else
			temp[1] = ft_strdup(envp[i[1]]);
		if (len < ft_strlen(temp[1]))
			len = ft_strlen(temp[1]);
		if (!ft_strncmp(temp[1], temp[0], len))
			return (ft_free(temp[0], temp[1]));
		ft_free(temp[1], NULL);
	}
	ft_free(temp[0], NULL);
	return (0);
}

char	**ft_setenv(char *var, char *value, char **envp, int n)
{
	int		i[2];
	char	*temp[2];

	if (n < 0)
		n = ft_strlen(var);
	i[0] = -1;
	temp[0] = ft_strjoin(var, "=");
	temp[1] = ft_strjoin(temp[0], value);
	ft_free(temp[0], NULL);
	while (!ft_strchr(var, '=') && envp && envp[++i[0]])
	{
		i[1] = n;
		if (i[1] < ft_strchri(envp[i[0]], '='))
			i[1] = ft_strchri(envp[i[0]], '=');
		if (!ft_strncmp(envp[i[0]], var, i[1]))
		{
			temp[0] = envp[i[0]];
			envp[i[0]] = temp[1];
			ft_free(temp[0], NULL);
			return (envp);
		}
	}
	envp = ft_array_expand(envp, temp[1]);
	ft_free(temp[1], NULL);
	return (envp);
}

int	ft_unset(t_main *ptr)
{
	char	**cmd;
	char	*temp;
	int		i[2];

	i[0] = 0;
	cmd = ((t_cmd *)ptr->cmds->content)->cmd_array;
	if (ft_array_size(cmd) >= 2)
	{
		while (cmd[++i[0]])
		{
			if (cmd[i[0]][0] == '-')
			{
				ft_error("unset: invalid option", 0, 2);
				return (2);
			}
			if (ft_strlen(cmd[i[0]]) > 0 && ft_strchri(cmd[i[0]], '=') == -1)
			{
				temp = ft_strjoin_free(cmd[i[0]], "=", 1);
				cmd[i[0]] = temp;
			}
			if (var_in_envp(ptr->environ, cmd[i[0]], i))
				ft_array_replace(&ptr->environ, NULL, i[1]);
		}
	}
	return (0);
}
