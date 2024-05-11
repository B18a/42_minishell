/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:44:30 by psanger           #+#    #+#             */
/*   Updated: 2024/05/03 15:25:54 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_builtin_child(t_msh *list, int if_exit, t_env **env)
{
	int	i;

	i = 0;
	if (list == NULL) {
		write(2, "ERROR LIST\n", 12);
		exit(-1);
	}
	if (ft_strncmp (list->cmd_args[0], "echo", 5) == 0) {
		printf("\033[0;32m %s : %d\033[0m\n", list->cmd_args[0], if_exit);
		// ft_echo();
	}
	else if (ft_strncmp (list->cmd_args[0], "cd", 3) == 0) {
		printf("\033[0;32m %s : %d\033[0m\n", list->cmd_args[0], if_exit);
		ft_cd(env, list->cmd_args[1]);
	}
	else if (ft_strncmp (list->cmd_args[0], "pwd", 4) == 0) {
		printf("\033[0;32m %s : %d\033[0m\n", list->cmd_args[0], if_exit);
		ft_pwd();
	}
	else if (ft_strncmp (list->cmd_args[0], "env", 4) == 0) {
		printf("\033[0;32m %s : %d\033[0m\n", list->cmd_args[0], if_exit);
		if (list->cmd_args[1] != NULL) {
			write(2, "env: no such file or dir\n", 26);
			exit(127);
		}
		ft_env(env);
	}
	else if (ft_strncmp (list->cmd_args[0], "export", 7) == 0) {
		printf("\033[0;32m %s : %d\033[0m\n", list->cmd_args[0], if_exit);
		if (list->cmd_args[1] == NULL)
			ft_export(env, NULL);
		while(list->cmd_args[++i] != NULL)
			ft_export(env, list->cmd_args[i]);
	}
	else if (ft_strncmp (list->cmd_args[0], "unset", 6) == 0) {
		printf("\033[0;32m %s : %d\033[0m\n", list->cmd_args[0], if_exit);
		while(list->cmd_args[++i] != NULL)
			ft_unset(env, list->cmd_args[i]);
	}
	// free all;
	exit(0);
}

int	exec_builtin_parent(t_msh *list, int if_exit, t_env **env)
{
	int	i;

	i = 0;
	if (list == NULL) {
		write(2, "ERROR LIST\n", 12);
		return (-1);
	}
	if (ft_strncmp (list->cmd_args[0], "echo", 5) == 0) {
		printf("\033[0;32m %s : %d\033[0m\n", list->cmd_args[0], if_exit);
		// ft_echo();
	}
	else if (ft_strncmp (list->cmd_args[0], "cd", 3) == 0) {
		printf("\033[0;32m %s : %d\033[0m\n", list->cmd_args[0], if_exit);
		ft_cd(env, list->cmd_args[1]);
	}
	else if (ft_strncmp (list->cmd_args[0], "pwd", 4) == 0) {
		printf("\033[0;32m %s : %d\033[0m\n", list->cmd_args[0], if_exit);
		ft_pwd();
	}
	else if (ft_strncmp (list->cmd_args[0], "env", 4) == 0) {
		printf("\033[0;32m %s : %d\033[0m\n", list->cmd_args[0], if_exit);
		if (list->cmd_args[1] != NULL) {
			write(2, "env: no such file or dir\n", 26);
			return (127);
		}
		ft_env(env);
	}
	else if (ft_strncmp (list->cmd_args[0], "export", 7) == 0) {
		printf("\033[0;32m %s : %d\033[0m\n", list->cmd_args[0], if_exit);
		if (list->cmd_args[1] == NULL)
			ft_export(env, NULL);
		while(list->cmd_args[++i] != NULL)
			ft_export(env, list->cmd_args[i]);
	}
	else if (ft_strncmp (list->cmd_args[0], "unset", 6) == 0) {
		printf("\033[0;32m %s : %d\033[0m\n", list->cmd_args[0], if_exit);
		while(list->cmd_args[++i] != NULL)
			ft_unset(env, list->cmd_args[i]);
	}
	return (0);
}
