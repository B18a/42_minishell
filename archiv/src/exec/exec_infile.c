/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:10:04 by psanger           #+#    #+#             */
/*   Updated: 2024/04/29 16:16:27 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_infile(t_msh *list, int if_exit, t_env **env)
{
	if (list == NULL)
	{
		write(2, "ERROR, PROBLEM WITH LIST\n", 26);
		exit(1);
	}
	int fd = open(list->cmd_args[0], O_RDONLY);
	if (fd < 0) {
		printf("%s: No such file or directory\n", list->cmd_args[0]);
		return ;
	}
	// if (list->exec != TRUE)
	// 	return ;
	if (dup2(fd, STDIN_FILENO) < 0)
		exit(1);
	close(fd);
	handler(list->left, if_exit, env);
}
