/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_append.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:53:56 by psanger           #+#    #+#             */
/*   Updated: 2024/04/09 21:55:55 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_append(t_minishell *list)
{
	int fd;

	if (list == NULL)
	{
		write(2, "ERROR, PROBLEM WITH LIST\n", 26);
		exit(1);
	}
	fd = open(list->value->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		write(2, "ERROR, PROBLEM OPEN\n", 21);
		exit(1);
	}
	if (list->value->exec == FALSE) {
		close(fd);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close (fd);
	handler(list->left);
	return ;
}
