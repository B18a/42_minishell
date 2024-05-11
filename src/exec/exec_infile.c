/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:10:04 by psanger           #+#    #+#             */
/*   Updated: 2024/05/10 22:29:13 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_infile(t_msh *list, int if_exit, t_env **env)
{
	if (list == NULL)
	{
		write(2, "ERROR, PROBLEM WITH LIST\n", 26);
		mid_free_exit(1, env, NULL);
	}
	// if(access(list->cmd_args[0], F_OK) == -1)
	// {
	// 	fprintf(stderr, "INFILEACCES\n");
	// 	mid_free_exit(126, env, list->root);
	// }
	int fd = open(list->cmd_args[0], O_RDONLY);
	if (fd < 0) {
		write(2, "minishell: ", 12);
		ft_putstr_fd(list->cmd_args[0], 2);
		write(2, ": No such file or directory\n", 29);
		exit(1);
		// mid_exit_free(1, env, root)
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		exit(1);
	close(fd);
	handler(list->left, if_exit, env);
}


// output nochmal anschauen bei fd < 0
