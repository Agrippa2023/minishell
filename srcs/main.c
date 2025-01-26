/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 19:43:33 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/23 09:10:14 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_main	*ptr;
	char	*prompt;
	char	*line;
	int		r;

	ptr = init_main(argv, envp);
	get_history(ptr);
	while (argc && argv && ttyname(STDIN_FILENO))
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		prompt = get_prompt(ptr);
		line = readline(prompt);
		ft_free(prompt, NULL);
		if (!check_line(line, ptr))
			break ;
	}
	free_ptr();
	r = get_ext()->exit_status;
	ft_free(get_ext(), NULL);
	rl_clear_history();
	exit (r);
}
