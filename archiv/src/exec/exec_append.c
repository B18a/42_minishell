/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_append.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:53:56 by psanger           #+#    #+#             */
/*   Updated: 2024/05/03 15:38:28 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_append(t_msh *list, int if_exit, t_env **env)
{
	fprintf(stderr, "\033[0;32m TEST\n\033[0m\n");
	int fd;

	if (list == NULL)
	{
		write(2, "ERROR, PROBLEM WITH LIST\n", 26);
		exit(1);
	}
	fd = open(list->cmd_args[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		write(2, "ERROR, PROBLEM OPEN\n", 21);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close (fd);
	handler(list->left, if_exit, env);
	return ;
}
