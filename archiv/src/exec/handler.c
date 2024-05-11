/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:14:22 by psanger           #+#    #+#             */
/*   Updated: 2024/05/03 16:12:20 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	piping(t_msh *list, int if_exit, t_env **env)
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
		handler(list->left, if_exit, env);
	}
	if (pid > 0) {
		exec_pipe_read(pfd);
		if (list->right->type == PIPE) {
			handler(list->right, if_exit, env);
			waitpid(pid, NULL, 0);
		}
		else {
			exec_last_cmd(list->right, if_exit, env);
			waitpid(pid, NULL, 0);
		}
	}
}


void	handler(t_msh *list, int if_exit, t_env **env)
{
	// fprintf(stderr, "TEST%d\n", list->type);
	if (list->type == PIPE) {
		piping(list, if_exit, env);
		//printf("PIPE\n");
	}
	else if (list->type == CMD) {
		exec_cmd(list);
	}
	else if (list->type == INFILE) {
		exec_infile(list, if_exit, env);
		// printf("INFILE\n");
	}
	else if (list->type == OUTFILE) {
		exec_outfile(list, if_exit, env);
		// printf("OUTFILE\n");
	}
	else if (list->type == APPEND) {
		exec_append(list, if_exit, env);
		// printf("APPEND\n");
	}
	else if (list->type == HEREDOC) {
		exec_heredoc(list, if_exit, env);
		// printf("HEREDOC\n");
	}
	else if (list->type == BUILTIN && if_exit == CMD) {
		exec_builtin_child(list, if_exit, env);
		// printf("BUILDIN\n");
	}
	else if (list->type == BUILTIN && if_exit == BUILTIN) {
		exec_builtin_parent(list, if_exit, env);
		// printf("BUILDIN\n");
	}
}

int		pre_exec(t_msh *list, t_env **env)
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
		handler(list, BUILTIN, env);
		return (0);
	}
	return (1);
}

void	minishell_exec(t_msh *list, t_env **env)
{
	if (list == NULL)
		return ;
	int pid;
	if (list->type != PIPE)
		if (pre_exec(list, env) == 0)
			return ;
	pid = fork();
	if (pid < 0) {
		write(2, "ERROR FORK\n", 12);
		exit(1);
	}
	if (pid == 0) {
		handler(list, CMD, env);
	}
	if (pid > 0) {
		waitpid(pid, NULL, 0);
	}
}
