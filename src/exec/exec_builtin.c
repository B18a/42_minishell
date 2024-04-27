/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:44:30 by psanger           #+#    #+#             */
/*   Updated: 2024/04/26 13:44:43 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_builtin_child(t_msh *list, int if_exit)
{
	if (list == NULL) {
		write(2, "ERROR LIST\n", 12);
		return ;
	}
	if (ft_strncmp (list->cmd_args[0], "echo", 5) == 0) {
		printf("echo : %s : %d\n", list->cmd_args[0], if_exit);
		// ft_echo();
	}
	else if (ft_strncmp (list->cmd_args[0], "cd", 3) == 0) {
		printf("cd : %s : %d\n", list->cmd_args[0], if_exit);
		// ft_cd();
	}
	else if (ft_strncmp (list->cmd_args[0], "pwd", 4) == 0) {
		printf("pwd : %s : %d\n", list->cmd_args[0], if_exit);
		// ft_pwd();
	}
	else if (ft_strncmp (list->cmd_args[0], "env", 4) == 0) {
		printf("env : %s : %d\n", list->cmd_args[0], if_exit);
		// ft_env();
	}
	else if (ft_strncmp (list->cmd_args[0], "export", 7) == 0) {
		printf("export : %s : %d\n", list->cmd_args[0], if_exit);
		// ft_export();
	}
	else if (ft_strncmp (list->cmd_args[0], "unset", 6) == 0) {
		printf("unset : %s : %d\n", list->cmd_args[0], if_exit);
		// ft_unset();
	}
	// free all (alles freen, child hat alles kopiert)
	exit (0);
}

void	exec_builtin_parent(t_msh *list, int if_exit)
{
	if (list == NULL) {
		write(2, "ERROR LIST\n", 12);
		return ;
	}
	if (ft_strncmp (list->cmd_args[0], "echo", 5) == 0) {
		printf("echo : %s : %d\n", list->cmd_args[0], if_exit);
		// ft_echo();
	}
	else if (ft_strncmp (list->cmd_args[0], "cd", 3) == 0) {
		printf("cd : %s : %d\n", list->cmd_args[0], if_exit);
		// ft_cd();
	}
	else if (ft_strncmp (list->cmd_args[0], "pwd", 4) == 0) {
		printf("pwd : %s : %d\n", list->cmd_args[0], if_exit);
		// ft_pwd();
	}
	else if (ft_strncmp (list->cmd_args[0], "env", 4) == 0) {
		printf("env : %s : %d\n", list->cmd_args[0], if_exit);
		// ft_env();
	}
	else if (ft_strncmp (list->cmd_args[0], "export", 7) == 0) {
		printf("export : %s : %d\n", list->cmd_args[0], if_exit);
		// ft_export();
	}
	else if (ft_strncmp (list->cmd_args[0], "unset", 6) == 0) {
		printf("unset : %s : %d\n", list->cmd_args[0], if_exit);
		// ft_unset();
	}
}
