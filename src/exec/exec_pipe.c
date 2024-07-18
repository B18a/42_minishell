/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:32:17 by psanger           #+#    #+#             */
/*   Updated: 2024/05/24 16:42:02 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_pipe_write(int pipe_read, int pipe_write)
{
	if (close(pipe_read) < 0)
	{
		write(2, "ERROR CLOSE\n", 13);
		exit(1);
	}
	if (dup2(pipe_write, STDOUT_FILENO) < 0)
	{
		write(2, "DUP2 ERROR\n", 12);
		exit(1);
	}
	if (close(pipe_write) < 0)
	{
		write(2, "ERROR CLOSE\n", 13);
		exit(1);
	}
}

void	exec_pipe_read(int pipe_read, int pipe_write)
{
	if (close(pipe_write) < 0)
	{
		write(2, "ERROR CLOSE\n", 13);
		exit(1);
	}
	if (dup2(pipe_read, STDIN_FILENO) < 0)
	{
		write(2, "DUP2 ERROR1\n", 12);
		exit(1);
	}
	if (close(pipe_read) < 0)
	{
		write(2, "ERROR CLOSE1\n", 13);
		exit(1);
	}
}
