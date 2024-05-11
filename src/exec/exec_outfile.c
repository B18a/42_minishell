/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:32:15 by psanger           #+#    #+#             */
/*   Updated: 2024/05/10 22:27:17 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_outfile(t_msh *list, int if_exit, t_env **env)
{
	int	fd;

	if (list == NULL)
	{
		write(2, "ERROR, PROBLEM WITH LIST\n", 26);
		mid_free_exit(1, env, NULL);
	}
	// if(access(list->cmd_args[0], F_OK) == -1)
	// {
	// 	// fprintf(stderr, "OUTFILEACCES\n");
	// 	// mid_free_exit(1, env, list->root);
	// }
	fd = open(list->cmd_args[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	handler(list->left, if_exit, env);
}

// if fd < 0 --> permission denied error + output
// outfile mit spaces
