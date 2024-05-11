/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:14:22 by psanger           #+#    #+#             */
/*   Updated: 2024/05/10 22:41:58 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	piping(t_msh *list, int if_exit, t_env **env)
// {
// 	int pfd[2];
// 	int pid;
// 	int pid2;
// 	int exit_code1;
// 	int exit_code2;
// 	int test = dup(STDIN_FILENO);

// 	exit_code1 = 0;
// 	exit_code2 = 0;
// 	if (pipe(pfd) < 0) {
// 		write(2, "ERROR CREATE PIPE\n", 19);
// 		exit(1);
// 	}
// 	pid = fork();
// 	if (pid < 0) {
// 		write(2, "ERROR FORK\n", 12);
// 		exit(1);
// 	}
// 	if (pid == 0) {
// 		exec_pipe_write(pfd);

// 		handler(list->left, if_exit, env);
// 	}
// 	pid2 = fork();
// 	if (pid2 == 0) {
// 		exec_pipe_read(pfd);
// 		handler(list->right, if_exit, env);
// 	}
// 	waitpid(pid, &exit_code1, 0);
// 	waitpid(pid2, &exit_code2, 1);
// 	exit(exit_code2);
// }


// void	piping(t_msh *list, int if_exit, t_env **env)
// {
// 	int pfd[2];
// 	int pid;
// 	int exit_code;

// 	exit_code = 0;
// 	if (pipe(pfd) < 0) {
// 		write(2, "ERROR CREATE PIPE\n", 19);
// 		exit(1);
// 	}
// 	pid = fork();
// 	if (pid < 0) {
// 		write(2, "ERROR FORK\n", 12);
// 		exit(1);
// 	}
// 	if (pid == 0) {
// 		exec_pipe_write(pfd[p_read], pfd[p_write]);
// 		handler(list->left, if_exit, env);
// 	}
// 	if (pid > 0) {
// 		if (list->right->type == PIPE) {
// 			exec_pipe_read(pfd[p_read], pfd[p_write]);
// 			handler(list->right, if_exit, env);
// 			waitpid(pid, &exit_code, 0);
// 		}
// 		else {
// 			exec_last_cmd(list->right, if_exit, env, pid, pfd[p_read], pfd[p_write]);
// 		}
// 	}
// }

void	piping(t_msh *list, int if_exit, t_env **env)
{
	int		pfd[2];
	int		exit_code;
	int		pid1;
	int		pid2;

	if (pipe(pfd) < 0) {
		write(2, "ERROR CREATE PIPE\n", 19);
		exit(1);
	}
	pid1 = fork();
	// child1 + parent
	if (pid1 == 0) {
		// child1 --> pid1 == 0
		exec_pipe_write(pfd[0], pfd[1]);
		handler(list->left, if_exit, env);// --> child1 stirbt
	}
	// parent
	pid2 = fork();
	// child2 + parent
	if (pid2 == 0) {
		// child 2 --> pid2 == 0
		exec_pipe_read(pfd[0], pfd[1]);
		handler(list->right, if_exit, env);// --> child2 stirbt
	}
	// parent
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid1, &exit_code, 0); // warten bis child 1 fertig
	waitpid(pid2, &exit_code, 0); // warten bis child 2 fertig
	exit (WEXITSTATUS(exit_code));
}

// void	piping(t_msh *list, int if_exit, t_env **env)
// {

// 	int pfd[2];
// 	int pid = 0;
// 	int pid2 = 0;
// 	int exit_code;
// 	int	last_cmd;

// 	last_cmd = 0;
// 	exit_code = 0;
// 	if (pipe(pfd) < 0)
// 	{
// 		write(2, "ERROR CREATE PIPE\n", 19);
// 		exit(1);
// 	}
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		exec_pipe_write(pfd[p_read], pfd[p_write]);
// 		handler(list->left, if_exit, env);
// 	}
// 	if (list->right->type == PIPE)
// 	{
// 		exec_pipe_read(pfd[p_read], pfd[p_write]);
// 		handler(list->right, if_exit, env);
// 		waitpid(pid, &exit_code, 0);
// 	}
// 	else
// 	{
// 		pid2 = fork();
// 		if (pid2 == 0)
// 		{
// 			last_cmd = 1;
// 			exec_pipe_read(pfd[p_read], pfd[p_write]);
// 			handler(list->right, if_exit, env);
// 		}
// 	}
// 	exec_pipe_read(pfd[p_read], pfd[p_write]);
// 	if (last_cmd == 1) {
// 		waitpid(pid2, &exit_code, 0);
// 		exit(exit_code);
// 	}
// }


int		handler(t_msh *list, int if_exit, t_env **env)
{
	int	exit_code = 0;

	if (list->type == PIPE)
		piping(list, if_exit, env);
	else if (list->type == CMD)
		exec_cmd(list, env);
	else if (list->type == INFILE)
		exec_infile(list, if_exit, env);
	else if (list->type == OUTFILE)
		exec_outfile(list, if_exit, env);
	else if (list->type == APPEND)
		exec_append(list, if_exit, env);
	else if (list->type == HEREDOC)
		exec_heredoc(list, if_exit, env);
	else if (list->type == BUILTIN)
		exit_code = exec_builtin(list, if_exit, env);

	return (exit_code);
	// alles int funktions --> exit code fuer builtins

}

int		pre_exec(t_msh *list, t_env **env)
{
	t_msh *curr;
	int exit_code = 0;

	curr = list;
	while (curr->left != NULL) {
		if (curr->type == PIPE || curr->type == CMD)
			return (1);
		curr = curr->left;
	}
	if (curr->type == PIPE || curr->type == CMD)
		return (-10000);
	if (curr->type == BUILTIN) {
		exit_code = handler(list, BUILTIN, env);
		return (exit_code);
	}
	return (-10000);
}

void	ctrl_c_in_child(int signal)
{
	(void)signal;
	exit(130);
}

int	minishell_exec(t_msh *list, t_env **env)
{
	int	exit_code;

	exit_code = 0;
	if (list == NULL)
		return (-1);
	int pid;
	if (list->type != PIPE) {
		exit_code = pre_exec(list, env);
		if (exit_code > -9999)
			return(exit_code);
	}
// hier muss der exit code zur[ck] gegeben werden aus pre exec
	pid = fork();
	if (pid < 0) {
		write(2, "ERROR FORK\n", 12);
		exit(1);
	}
	if (pid == 0) {
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ctrl_c_in_child);
		handler(list, CMD, env);
	}
	waitpid(pid, &exit_code, 0);
	exit_code = WEXITSTATUS(exit_code);
	return (exit_code);
}
