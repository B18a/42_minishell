/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:10:19 by psanger           #+#    #+#             */
/*   Updated: 2024/04/27 13:22:58 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_last_cmd(t_msh *list, int if_exit)
{
	int pid2;

	pid2 = fork();
	if (pid2 < 0) {
		write(2, "ERROR CREATE PIPE\n", 19);
		exit(1);
	}
	if (pid2 == 0)
		handler(list, if_exit);
	if (pid2 > 0) {
		waitpid(pid2, NULL, 0);
	}

}


void	exec_cmd(t_msh *list)
{
	// char *path = get_path(list->cmd_args[0]);
	if (execve(list->cmd_path, list->cmd_args, NULL) == -1)
	{
		write(2, "Wrong Input1\n", 14);
		exit(127);
	}

	exit(1);
	// exit codes nochmal genauer anschauen
}



	// free den kack (variable muss davor gespeichert werden und dann
	// nach dem ausfuehren der execve gefreet werden wirder in der funktion davor)
