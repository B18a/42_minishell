/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:14:22 by psanger           #+#    #+#             */
/*   Updated: 2024/04/18 17:54:28 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	piping(t_minishell *list)
{
	int pfd[2];
	int pid;

	if (pipe(pfd) < 0) {
		write(2, "ERROR CREATE PIPE\n", 19);
		exit(1);
	}
	pid = fork();
	if (pid < 0) {
		write(2, "ERROR FORK\n", 12);
		exit(1);
	}
	if (pid == 0) {
		exec_pipe_write(pfd);
		handler(list->left);
	}
	if (pid > 0) {
		if (list->right->type == PIPE) {
			exec_pipe_read(pfd);
			handler(list->right);
			waitpid(pid, NULL, 0);
		}
		else {
			exec_pipe_read(pfd);
			exec_last_cmd(list->right);
		}
	}
}


void	handler(t_minishell *list)
{
	if (list->type == PIPE) {
		piping(list);
		//printf("PIPE\n");
	}
	else if (list->type == CMD) {
		exec_cmd(list);
		// printf("CMD\n");
	}
	else if (list->type == INFILE) {
		exec_infile(list);
		// printf("INFILE\n");
	}
	else if (list->type == OUTFILE) {
		exec_outfile(list);
		// printf("OUTFILE\n");
	}
	else if (list->type == APPEND) {
		exec_append(list);
		// printf("APPEND\n");
	}
	else if (list->type == HEREDOC) {
		exec_heredoc(list);
		// printf("HEREDOC\n");
	}
	else if (list->type == BUILTIN) {
		// exec_buildin(list);
		// printf("BUILDIN\n");
	}
}



void	minishell_exec(t_minishell *list)
{
	if (list == NULL)
		return ;
	int pid;
	// if (list->type != PIPE)
	// 	pre_exec(list);
	pid = fork();
	if (pid < 0) {
		write(2, "ERROR FORK\n", 12);
		exit(1);
	}
	if (pid == 0) {
		handler(list);
	}
	if (pid > 0) {
		waitpid(pid, NULL, 0);
	}
}
