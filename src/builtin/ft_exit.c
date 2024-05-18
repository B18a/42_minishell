/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:40:14 by psanger           #+#    #+#             */
/*   Updated: 2024/05/15 20:53:55 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit(char **argv, t_env **env, t_msh *list, int i)
{
	if (argv[1] == NULL)
		mid_free_exit(0, env, list);
	while (argv[1][++i] != '\0')
	{
		if (ft_isdigit(argv[1][i]) == 0 && argv[1][i] != '-' && argv[1][i] != '+')
		{
			putstr_fd("minishell: ", argv[1], ": numeric argument required\n", 2);
			mid_free_exit(255, env, list);
		}
	}
	if (argv[2] != NULL)
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		return (1);
	}
	mid_free_exit((unsigned char)ft_atoi(argv[1]), env, list);
	return (0);
}

// quotes noch nicht gehandelet
// is_digit + und -


