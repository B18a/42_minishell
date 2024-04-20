/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:10:19 by psanger           #+#    #+#             */
/*   Updated: 2024/04/11 00:26:00 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	exec_last_cmd(t_minishell *list)
{
	int pid2;

	pid2 = fork();
	if (pid2 < 0) {
		write(2, "ERROR CREATE PIPE\n", 19);
		exit(1);
	}
	if (pid2 == 0)
		handler(list);
	if (pid2 > 0) {
		waitpid(pid2, NULL, 0);
	}

}


void	exec_cmd(t_minishell *list)
{
	char *path = get_path(list->value->cmd);
	if (execve(path, list->value->cmd_args, NULL) == -1)
	{
		write(2, "Wrong Input1\n", 14);
		exit(127);
	}
	exit(1);
	// exit codes nochmal genauer anschauen
}



	// free den kack (variable muss davor gespeichert werden und dann
	// nach dem ausfuehren der execve gefreet werden wirder in der funktion davor)
