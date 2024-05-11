/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:40:14 by psanger           #+#    #+#             */
/*   Updated: 2024/05/08 15:08:45 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit(char **argv, t_env **env, t_msh *list, int i)
{
	t_env **silence_env = env;
	t_msh *silence = list;
	silence_env = NULL;
	silence = NULL;

	if (argv[1] == NULL)
		mid_free_exit(0, env, list);
	if (argv[1] != NULL)
	{
		while (argv[1][++i] != '\0')
		{
			if (ft_isdigit(argv[1][i]) == 0)
			{
				write(2, "minishell: ", 12);
				ft_putstr_fd(argv[1], 2);
				write(2, ": numeric argument required\n", 29);
				mid_free_exit(255, env, list);
			}
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


