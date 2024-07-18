/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 11:39:23 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/24 15:55:35 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env_start)
{
	t_env	*env;
	int		exit_code;

	exit_code = 0;
	env = NULL;
	signal(SIGINT, signal_c_handler);
	signal(SIGQUIT, SIG_IGN);
	if (argc != 1)
	{
		printf("%s, wrong num args\n", argv[0]);
		return (0);
	}
	env = get_env(env_start);
	ft_shell_lvl(&env);
	exit_code = get_input(&env);
	env_free(env);
	return (exit_code);
}
