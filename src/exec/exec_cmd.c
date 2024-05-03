/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:10:19 by psanger           #+#    #+#             */
/*   Updated: 2024/05/03 15:47:14 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_last_cmd(t_msh *list, int if_exit, t_env **env)
{
	int pid2;

	pid2 = fork();
	if (pid2 < 0) {
		write(2, "ERROR CREATE PIPE\n", 19);
		exit(1);
	}
	if (pid2 == 0) {
		handler(list, if_exit, env);
	}
	if (pid2 > 0) {
		waitpid(pid2, NULL, 0);
	}
	exit(0);
}


void	exec_cmd(t_msh *list)
{
	// fprintf(stderr, "TEST |%s|\n\n", list->cmd_args[0]);
	// char test[200];
	// if (ft_strncmp(list->cmd_args[0], "cat", 4) == 0) {
	// 	printf("hallo\n");
	// 	printf("hallo\n");
	// 	printf("hallo\n");
	// 	fprintf(stderr, "|IN IF|\n\n");
	// 	scanf("%s", test);
	// 	fprintf(stderr, "|%s|\n", test);
	// }
	if (execve(list->cmd_path, list->cmd_args, NULL) == -1)
	{
		write(2, "minishell : command not found\n", 31);
		exit(127);
	}

	// fprintf(stderr, "\033[0;32m FEHLER\n\033[0m\n");
	exit(1);
	// exit codes nochmal genauer anschauen
}



	// free den kack (variable muss davor gespeichert werden und dann
	// nach dem ausfuehren der execve gefreet werden wirder in der funktion davor)
