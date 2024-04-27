/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_append.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:53:56 by psanger           #+#    #+#             */
/*   Updated: 2024/04/25 22:45:34 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_append(t_msh *list, int if_exit)
{
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
	// if (list->exec == FALSE) {
	// 	close(fd);
	// 	return ;
	// }
	dup2(fd, STDOUT_FILENO);
	close (fd);
	handler(list->left, if_exit);
	return ;
}
