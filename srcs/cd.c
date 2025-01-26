/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 03:06:59 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/23 01:42:55 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	cd_errors(char **str[2])
{
	DIR		*dir;
	int		i;

	dir = NULL;
	i = ft_array_size(str[0]);
	if (i > 2)
	{
		ft_error("cd: too many arguments", 0, 1);
		return ;
	}
	if (str[0][1])
		dir = opendir(str[0][1]);
	if (!str[0][1] && str[1][0] && !str[1][0][0])
		ft_error("HOME not set", 0, 1);
	if (str[1][0] && !str[0][1])
		get_ext()->exit_status = chdir(str[1][0]) == -1;
	if (str[0][1] && dir && access(str[0][1], F_OK) != -1)
		chdir(str[0][1]);
	else if (str[0][1] && access(str[0][1], F_OK) == -1)
		ft_error(str[0][1], NO_DIR, 1);
	else if (str[0][1])
		ft_error(str[0][1], NOT_DIR, 1);
	if (str[0][1] && dir)
		closedir(dir);
}

static int	ft_cd_select(char	**str[2], t_main *ptr)
{
	char	*temp;

	temp = ft_getenv("HOME", ptr->environ, 4);
	if (!temp)
		temp = ft_strdup("");
	str[1] = ft_array_expand(NULL, temp);
	ft_free(temp, NULL);
	temp = getcwd(NULL, 0);
	str[1] = ft_array_expand(str[1], temp);
	ft_free(temp, NULL);
	cd_errors(str);
	if (get_ext()->exit_status == 0)
		ptr->environ = ft_setenv("OLDPWD", str[1][1], ptr->environ, 6);
	temp = getcwd(NULL, 0);
	if (!temp)
		temp = ft_strdup("");
	str[1] = ft_array_expand(str[1], temp);
	ft_free(temp, NULL);
	ptr->environ = ft_setenv("PWD", str[1][2], ptr->environ, 3);
	ft_array_free(&str[1]);
	return (get_ext()->exit_status);
}

int	ft_cd(t_main *ptr)
{
	t_list	*temp_list;
	char	**str[2];

	get_ext()->exit_status = 0;
	temp_list = ptr->cmds;
	while (temp_list)
	{
		if (!ft_strncmp(*((t_cmd *)temp_list->content)->cmd_array, "cd", 2))
			break ;
		temp_list = temp_list->next;
	}
	if (!temp_list)
		return (0);
	str[0] = ((t_cmd *)temp_list->content)->cmd_array;
	if (str[0][1] && ft_strlen(str[0][1]) > 0 && \
		!ft_strncmp(str[0][1], "-", ft_strlen(str[0][1])))
	{
		ft_free(str[0][1], NULL);
		str[0][1] = ft_getenv("OLDPWD", ptr->environ, 6);
		ft_putendl_fd(str[0][1], 1);
	}
	return (ft_cd_select(str, ptr));
}
