/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_append.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:53:56 by psanger           #+#    #+#             */
/*   Updated: 2024/05/24 21:30:15 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_append(t_msh *list, int if_exit, t_env **env)
{
	int	fd;

	if (list == NULL)
	{
		write(2, "ERROR, PROBLEM WITH LIST\n", 26);
		exit(1);
	}
	fd = open(list->cmd_args[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: out: Permission denied\n", 2);
		if (if_exit == CMD)
			mid_free_exit(1, env, list->root);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (handler(list->left, if_exit, env, list->root));
}
