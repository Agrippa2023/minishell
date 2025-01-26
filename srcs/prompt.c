/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 03:30:11 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/23 01:36:58 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_home(t_main *ptr)
{
	char	*home;
	char	*pwd;
	char	*temp;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("# ");
	home = ft_getenv("HOME", ptr->environ, 4);
	if (home && home[0] && ft_strnstr(pwd, home, ft_strlen(pwd)))
	{
		temp = pwd;
		pwd = ft_strjoin("~", pwd + ft_strlen(home));
		ft_free(temp, NULL);
	}
	ft_free(home, NULL);
	home = ft_strjoin(BLUE, pwd);
	ft_free(pwd, NULL);
	home = ft_strjoin_free(home, " ", 1);
	pwd = ft_strjoin(" ", home);
	ft_free(home, NULL);
	pwd = ft_strjoin_free(pwd, BLANK, 1);
	return (pwd);
}

static char	*get_user_post(t_main *ptr)
{
	char	*temp[2];
	int		i[2];

	temp[0] = ft_getenv("USER", ptr->environ, 4);
	temp[0] = ft_strjoin_free(temp[0], "@", 1);
	temp[1] = ft_getenv("SESSION_MANAGER", ptr->environ, 15);
	i[0] = ft_strchri(temp[1], '/');
	i[1] = ft_strchri(temp[1], '.');
	temp[1] = ft_substr_free(temp[1], i[0] + 1, (size_t)(i[1] - i[0] - 1), 1);
	temp[0] = ft_strjoin_free(temp[0], temp[1], 2);
	return (temp[0]);
}

char	*get_prompt(t_main *ptr)
{
	t_ext	*ext;
	char	*temp;
	char	*temp2;

	if (!ptr->environ || !ptr->environ[0])
		return (NULL);
	temp = get_user_post(ptr);
	temp2 = ft_strjoin_free(CYAN, temp, 0);
	ft_free(temp, NULL);
	temp = get_home(ptr);
	temp2 = ft_strjoin_free(temp2, temp, 2);
	ext = get_ext();
	if (ext->exit_status == 0 || ext->exit_status == -1)
		temp2 = ft_strjoin_free(temp2, GREEN, 1);
	else
		temp2 = ft_strjoin_free(temp2, RED, 1);
	temp2 = ft_strjoin_free(temp2, "Z> ", 1);
	temp2 = ft_strjoin_free(temp2, BLANK, 1);
	return (temp2);
}
