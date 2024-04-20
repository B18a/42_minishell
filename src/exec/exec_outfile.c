/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:32:15 by psanger           #+#    #+#             */
/*   Updated: 2024/04/09 21:56:11 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_outfile(t_minishell *list)
{
	int fd;

	if (list == NULL)
	{
		write(2, "ERROR, PROBLEM WITH LIST\n", 26);
		exit(1);
	}
	fd = open(list->value->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (list->value->exec == FALSE) {
		close(fd);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close (fd);
	handler(list->left);
	return ;
}
