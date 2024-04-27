/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:32:17 by psanger           #+#    #+#             */
/*   Updated: 2024/04/25 17:00:00 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_pipe_write(int *pfd)
{
	if (pfd == NULL) {
		write(2, "ERROR WITH PIPE\n", 17);
		exit(1);
	}
	if (close(pfd[p_read]) < 0) {
		write(2, "ERROR CLOSE\n", 13);
		exit(1);
	}
	if (dup2(pfd[p_write], STDOUT_FILENO) < 0) {
		write(2, "DUP2 ERROR\n", 12);
		exit(1);
	}
	if (close(pfd[p_write]) < 0) {
		write(2, "ERROR CLOSE\n", 13);
		exit(1);
	}
}


void	exec_pipe_read(int *pfd)
{
	if (pfd == NULL) {
		write(2, "ERROR WITH PIPE\n", 17);
		exit(1);
	}
	if (close(pfd[p_write]) < 0) {
		write(2, "ERROR CLOSE\n", 13);
		exit(1);
	}
	if (dup2(pfd[p_read], STDIN_FILENO) < 0) {
		write(2, "DUP2 ERROR1\n", 12);
		exit(1);
	}
	if (close(pfd[p_read]) < 0) {
		write(2, "ERROR CLOSE1\n", 13);
		exit(1);
	}
}

