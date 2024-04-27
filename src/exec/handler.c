/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:14:22 by psanger           #+#    #+#             */
/*   Updated: 2024/04/26 14:45:41 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	piping(t_msh *list, int if_exit)
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
		handler(list->left, if_exit);
	}
	if (pid > 0) {
		if (list->right->type == PIPE) {
			exec_pipe_read(pfd);
			handler(list->right, if_exit);
			waitpid(pid, NULL, 0);
		}
		else {
			exec_pipe_read(pfd);
			exec_last_cmd(list->right, if_exit);
		}
	}
}


void	handler(t_msh *list, int if_exit)
{
	// fprintf(stderr, "TEST%d\n", list->type);
	if (list->type == PIPE) {
		piping(list, if_exit);
		//printf("PIPE\n");
	}
	else if (list->type == CMD) {
		exec_cmd(list);
	}
	else if (list->type == INFILE) {
		exec_infile(list, if_exit);
		// printf("INFILE\n");
	}
	else if (list->type == OUTFILE) {
		exec_outfile(list, if_exit);
		// printf("OUTFILE\n");
	}
	else if (list->type == APPEND) {
		exec_append(list, if_exit);
		// printf("APPEND\n");
	}
	else if (list->type == HEREDOC) {
		exec_heredoc(list, if_exit);
		// printf("HEREDOC\n");
	}
	else if (list->type == BUILTIN && if_exit == CMD) {
		exec_builtin_child(list, if_exit);
		// printf("BUILDIN\n");
	}
	else if (list->type == BUILTIN && if_exit == BUILTIN) {
		exec_builtin_parent(list, if_exit);
		// printf("BUILDIN\n");
	}
}

int		pre_exec(t_msh *list)
{
	t_msh *curr;

	curr = list;
	while (curr->left != NULL) {
		if (curr->type == PIPE || curr->type == CMD)
			return (1);
		curr = curr->left;
	}
	if (curr->type == PIPE || curr->type == CMD)
		return (1);
	if (curr->type == BUILTIN) {
		handler(list, BUILTIN);
		printf("Builtin\n");
		printf("%s\n", curr->cmd_args[0]);
		return (0);
	}
	return (0);
}

void	minishell_exec(t_msh *list)
{
	if (list == NULL)
		return ;
	int pid;
	if (list->type != PIPE)
		if (pre_exec(list) == 0)
			return ;
	pid = fork();
	if (pid < 0) {
		write(2, "ERROR FORK\n", 12);
		exit(1);
	}
	if (pid == 0) {
		handler(list, CMD);
	}
	if (pid > 0) {
		waitpid(pid, NULL, 0);
	}
}
