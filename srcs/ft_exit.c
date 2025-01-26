/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:30:32 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/23 10:10:00 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

long long	ft_exit_atoi(char *nb, long long *nbr)
{
	int	sign;

	sign = 1;
	*nbr = 0;
	while (ft_isspace(*nb))
		nb++;
	if (*nb == '-' || *nb == '+')
	{
		if (*nb == '-')
			sign *= -1;
		nb++;
	}
	if (!ft_isdigit(*nb))
		return (-1);
	while (ft_isdigit(*nb))
	{
		*nbr = 10 * *nbr + (*nb - '0');
		nb++;
	}
	if (*nb && !ft_isspace(*nb))
		return (-1);
	*nbr *= sign;
	return (0);
}

static int	ft_print_exit_errors(t_cmd *node, int *do_exit, int mod)
{
	if (mod == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(node->cmd_array[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (2);
	}
	if (mod == 2)
	{
		*do_exit = 0;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

int	ft_exit(t_list *cmd, int *do_exit, int pipe)
{
	t_cmd		*node;
	long long	status[2];

	node = NULL;
	if (cmd)
	{
		node = cmd->content;
		*do_exit = !cmd->next;
	}
	if (*do_exit && !pipe)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!node || !node->cmd_array || !node->cmd_array[1])
		return (0);
	status[1] = ft_exit_atoi(node->cmd_array[1], &status[0]);
	if (status[1] == -1 || status[0] > INT_MAX || status[0] < INT_MIN)
		return (ft_print_exit_errors(node, do_exit, 1));
	else if (node->cmd_array[2])
		return (ft_print_exit_errors(node, do_exit, 2));
	status[0] %= 256 + 256 * (status[0] < 0);
	return ((int)status[0]);
}
