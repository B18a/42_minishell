/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:04:08 by psanger           #+#    #+#             */
/*   Updated: 2024/04/09 14:14:36 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// void	handler(t_minishell *list, int *pfd_1)
// {
// 	if (list->type == PIPE_WRITE) {
// 		exec_pipe_write(list, pfd_1);
// 		// printf("PIPE_WRITE\n");
// 	}
// 	else if (list->type == PIPE_READ) {
// 		exec_pipe_read(list, pfd_1);
// 		// printf("PIPE_READ\n");
// 	}
// 	else if (list->type == CMD) {
// 		exec_cmd(list);
// 		// printf("CMD\n");
// 	}
// 	else if (list->type == INFILE) {
// 		exec_infile(list);
// 		// printf("INFILE\n");
// 	}
// 	else if (list->type == OUTFILE) {
// 		exec_outfile(list);
// 		// printf("OUTFILE\n");
// 	}
// 	else if (list->type == APPEND) {
// 		exec_append(list);
// 		// printf("APPEND\n");
// 	}
// 	else if (list->type == HEREDOC) {
// 		// exec_heredoc(list);
// 		// printf("HEREDOC\n");
// 	}
// 	else if (list->type == BUILDIN) {
// 		// exec_buildin(list);
// 		// printf("BUILDIN\n");
// 	}
// }
// void	no_pipe(t_minishell *list)
// {
// 	t_minishell *curr;

// 	curr = list;
// 	int pid = fork();
// 	if (pid < 0) {
// 		write(2, "ERROR FORK\n", 12);
// 		exit(1);
// 	}
// 	else if (pid == 0)
// 	{
// 		while (curr != NULL)
// 		{
// 			handler(curr, NULL);
// 			curr = curr->next;
// 		}
// 	}
// 	else
// 		waitpid(pid, NULL, 0);
// }


// t_minishell	*parrent(t_minishell *curr)
// {
// 	// if (curr != NULL && curr->type == PIPE_READ) {
// 	// 	// free(curr);
// 	// 	// if (curr != NULL)
// 	// 	// 	write(2, "parrent : pipe read\n", 21);
// 	// 	curr = curr->next;
// 	// }
// 	// if (curr != NULL && curr->type == PIPE_WRITE) {
// 	// 	// free(curr);
// 	// 	// if (curr != NULL)
// 	// 	// 	write(2, "parrent : pipe write\n", 22);
// 	// 	curr = curr->next;
// 	// }
// 	// // printf("parrent test 2, %d\n", curr->type);
// 	// while (curr != NULL && curr->type != PIPE_WRITE && curr->type != PIPE_READ) {
// 	// 	// free(curr);
// 	// 	// if (curr != NULL && curr->type != CMD)
// 	// 	// 	write(2, "parrent : redirect\n", 20);
// 	// 	// if (curr != NULL && curr->type == CMD)
// 	// 	// 	write(2, "parrent : cmd\n", 15);
// 	// 	curr = curr->next;
// 	// }

// 	while (curr != NULL && curr->type != CMD) {
// 		curr = curr->next;
// 	}
// 	if (curr != NULL && curr->type == CMD) {
// 		curr = curr->next;
// 	}
// 	if (curr == NULL)
// 		return (NULL);
// 	return (curr);
// }


// void	child(t_minishell *curr, int *pfd)
// {
// 	// if (curr != NULL && curr->type == PIPE_READ) {
// 	// 	// if (curr != NULL)
// 	// 		// write(2, "child : pipe read\n", 19);
// 	// 	handler(curr,pfd);
// 	// 	curr = curr->next;
// 	// }
// 	// if (curr != NULL && curr->type == PIPE_WRITE) {
// 	// 	// if (curr != NULL)
// 	// 		// write(2, "child : pipe write\n", 20);
// 	// 	handler(curr, pfd);
// 	// 	curr = curr->next;
// 	// }
// 	// while (curr != NULL && curr->type != PIPE_WRITE && curr->type != PIPE_READ) {
// 	// 	// if (curr != NULL && curr->type != CMD)
// 	// 	// 	write(2, "child : redirect\n", 18);
// 	// 	// if (curr != NULL && curr->type == CMD)
// 	// 	// 	write(2, "child : cmd\n", 13);
// 	// 	handler(curr, NULL);
// 	// 	curr = curr->next;
// 	// }
// 	while (curr != NULL && curr->type != CMD) {
// 		handler(curr, pfd);
// 		curr = curr->next;
// 	}
// 	if (curr != NULL && curr->type == CMD) {
// 		handler(curr, pfd);
// 		curr = curr->next;
// 	}
// }

// void	piping(t_minishell *list)
// {
// 	t_minishell *curr = list;

// 	int pid;
// 	int pfd[2];

// 	while (curr != NULL)
// 	{
// 		if (pipe(pfd) < 0) {
// 			write(2, "ERROR CREATE PUPE\n", 19);
// 			exit(1);
// 		}
// 		pid = fork();
// 		if (pid < 0) {
// 			write(2, "ERROR CREATE PIPE\n", 19);
// 			exit (1);
// 		}
// 		else if (pid == 0) {				// child
// 			child(curr, pfd);
// 		}
// 		else if (pid > 0) {				// parrent
// 			sleep(1);
// 			curr = parrent(curr);
// 		}
// 	}
// }

// void	minishell_exec(t_minishell *list)
// {
// 	bool bool_pipe = TRUE;

// 	if (bool_pipe == FALSE)
// 		no_pipe(list);
// 	if (bool_pipe == TRUE)
// 		piping(list);
// }


// 	// t_minishell *curr = list;

// 	// // erster durchlauf
// 	// int pid1;
// 	// pid1 = fork();
// 	// if (pid1 < 0)
// 	// 	exit(1);
// 	// if (pid1 == 0)
// 	// {
// 	// 	while (curr != NULL)
// 	// 	{
// 	// 		handler(curr);
// 	// 		curr = curr->next;
// 	// 	}
// 	// 	write(2, "Fehler\n", 8);
// 	// }
// 	// // zweiter durchlauf
// 	// waitpid(pid1, NULL, 0);
// 	// while (curr->type != PIPE_READ && curr != NULL)
// 	// 	curr = curr->next;

// 	// pid1 = fork();
// 	// if (pid1 < 0)
// 	// 	exit(1);
// 	// if (pid1 == 0)
// 	// {
// 	// 	while (curr != NULL)
// 	// 	{
// 	// 		handler(curr);
// 	// 		curr = curr->next;
// 	// 	}
// 	// 	write(2, "Fehler\n", 8);
// 	// }
