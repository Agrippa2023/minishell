/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 19:35:23 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/23 10:07:18 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	void	split_and_trim(t_main *ptr, char ***argv)
{
	int		i;
	int		quotes[2];
	char	**temp_array[2];
	char	*temp;

	i = -1;
	temp_array[1] = *argv;
	while (temp_array[1] && temp_array[1][++i])
	{
		temp = ft_strdup(temp_array[1][i]);
		temp = expand_variables(temp, -1, ptr);
		temp = expand_path(temp, -1, \
							quotes, ft_getenv("HOME", ptr->environ, 4));
		if (!temp)
			temp_array[1] = ft_array_contract(&temp_array[1], i--);
		else
		{
			temp_array[0] = cmds_split_trim(temp, "<|>");
			temp_array[1] = ft_array_replace(&temp_array[1], temp_array[0], i);
			i += ft_array_size(temp_array[0]) - 1;
			ft_array_free(&temp_array[0]);
			ft_free(temp, NULL);
		}
	}
	*argv = temp_array[1];
}

static void	*parsing(t_main *ptr, char **argv)
{
	int		do_exit;
	t_ext	*ext;

	do_exit = 0;
	ext = get_ext();
	ptr->cmds = fill_list(argv, -1);
	if (!ptr->cmds)
		return (ptr);
	ext->exit_status = builtin(ptr, ptr->cmds, &do_exit, 0);
	if (!do_exit && ext->exit_status == 13)
		ext->exit_status = 0;
	if (ext->exit_status > 255)
		ext->exit_status /= 255;
	if (argv && do_exit)
	{
		ft_lstclear(&ptr->cmds, free_lst);
		return (NULL);
	}
	get_ext()->exit_status = ext->exit_status;
	return (ptr);
}

static char	*ft_array_to_string(char ***array)
{
	char	*str;
	char	**temp;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	temp = *array;
	while (temp[i[0]])
		i[1] += ft_strlen(temp[i[0]++]) + 1;
	str = malloc(sizeof(char) * (i[1] + 1));
	if (!str)
		return (NULL);
	i[0] = 0;
	while (temp[i[0]])
	{
		i[1] = 0;
		while (temp[i[0]][i[1]])
			str[i[2]++] = temp[i[0]][i[1]++];
		str[i[2]++] = ' ';
		i[0]++;
	}
	str[i[2]] = '\0';
	ft_array_free(array);
	return (str);
}

static void	*further_check_line(t_main *ptr, char **args_array)
{
	t_cmd	*cmd;
	char	*temp_line;

	split_and_trim(ptr, &args_array);
	temp_line = NULL;
	if (args_array)
		temp_line = ft_array_to_string(&args_array);
	args_array = split_and_check_quotes(temp_line, " ");
	if (temp_line)
		ft_free(temp_line, NULL);
	ptr = parsing(ptr, args_array);
	if (ptr && ptr->cmds)
		cmd = ptr->cmds->content;
	if (ptr && ptr->cmds && cmd && cmd->cmd_array && ft_lstsize(ptr->cmds) == 1)
		ptr->environ = ft_setenv("_", cmd->cmd_array[0], ptr->environ, 1);
	if (ptr && ptr->cmds)
		ft_lstclear(&ptr->cmds, free_lst);
	return (ptr);
}

void	*check_line(char *line, t_main *ptr)
{
	char	**args_array;

	if (!line)
	{
		ft_putendl_fd("exit", 1);
		return (NULL);
	}
	add_to_history(ptr, line);
	if (ft_count_redir(line, 0))
		return (ptr);
	args_array = split_and_check_quotes(line, " ");
	ft_free(line, NULL);
	if (!args_array)
	{
		ft_error(NULL, QUOTE, 1);
		return ("");
	}
	if (args_array[0] && args_array[0][0] == '|')
	{
		ft_array_free(&args_array);
		ft_error(NULL, PIPE_ENDERR, 2);
		return ("");
	}
	return (further_check_line(ptr, args_array));
}
