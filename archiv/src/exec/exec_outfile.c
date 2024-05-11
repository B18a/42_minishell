/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:32:15 by psanger           #+#    #+#             */
/*   Updated: 2024/05/03 16:09:52 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_outfile(t_msh *list, int if_exit, t_env **env)
{
	int fd;

	if (list == NULL)
	{
		write(2, "ERROR, PROBLEM WITH LIST\n", 26);
		exit(1);
	}
	fd = open(list->cmd_args[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close (fd);
	handler(list->left, if_exit, env);
}
