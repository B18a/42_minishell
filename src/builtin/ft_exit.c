/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:40:14 by psanger           #+#    #+#             */
/*   Updated: 2024/05/24 22:00:13 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit(char **argv, t_env **env, t_msh *list, int i)
{
	if (argv[1] == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		mid_free_exit(0, env, list->root);
	}
	while (argv[1][++i] != '\0')
	{
		if (ft_isdigit(argv[1][i]) == 0 && argv[1][i] != '-'
			&& argv[1][i] != '+')
		{
			putstr_fd("exit\nminishell: exit: ", argv[1],
				": numeric argument required\n", 1);
			mid_free_exit(255, env, list->root);
		}
	}
	if (argv[2] != NULL)
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		return (1);
	}
	ft_putstr_fd("exit\n", 1);
	mid_free_exit((unsigned char)ft_atoi(argv[1]), env, list->root);
	return (0);
}
