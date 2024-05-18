/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:44:30 by psanger           #+#    #+#             */
/*   Updated: 2024/05/15 21:04:30 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_builtin(t_msh *list, int if_exit, t_env **env)
{
	int	i;
	int	exit_code;

	i = 0;
	exit_code = 0;
	if (list == NULL)
	{
		write(2, "ERROR LIST\n", 12);
		if (if_exit == CMD)
			exit(1);
		else
			return (1);
	}
	if (ft_strncmp(list->cmd_args[0], "echo", 5) == 0)
		exit_code = ft_echo(list->cmd_args);
	else if (ft_strncmp(list->cmd_args[0], "cd", 3) == 0)
		exit_code = ft_cd(env, list->cmd_args[1]);
	else if (ft_strncmp(list->cmd_args[0], "pwd", 4) == 0)
		exit_code = ft_pwd();
	else if (ft_strncmp(list->cmd_args[0], "env", 4) == 0)
		exit_code = ft_env(env, list->cmd_args);
	else if (ft_strncmp(list->cmd_args[0], "export", 7) == 0)
	{
		if (list->cmd_args[1] == NULL)
			exit_code = ft_export(env, NULL);
		while (list->cmd_args[++i] != NULL)
			exit_code = ft_export(env, list->cmd_args[i]);
	}
	else if (ft_strncmp(list->cmd_args[0], "unset", 6) == 0)
	{
		while (list->cmd_args[++i] != NULL)
			exit_code = ft_unset(env, list->cmd_args[i]);
	}
	else if (ft_strncmp(list->cmd_args[0], "exit", 6) == 0)
		exit_code = ft_exit(list->cmd_args, env, list, -1);
	if (if_exit == CMD)
		mid_free_exit(exit_code, env, list->root);
	else if (if_exit == BUILTIN)
		return (exit_code);
	return (0);
}
