/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:14:22 by psanger           #+#    #+#             */
/*   Updated: 2024/05/17 15:36:30 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	piping(t_msh *list, int if_exit, t_env **env)
{
	int	pfd[2];
	int	exit_code;
	int	pid1;
	int	pid2;

	if (pipe(pfd) < 0)
	{
		write(2, "ERROR CREATE PIPE\n", 19);
		exit(1);
	}
	pid1 = fork();
	if (pid1 == 0)
	{
		exec_pipe_write(pfd[0], pfd[1]);
		handler(list->left, if_exit, env);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		exec_pipe_read(pfd[0], pfd[1]);
		handler(list->right, if_exit, env);
	}
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid1, &exit_code, 0);
	waitpid(pid2, &exit_code, 0);
	exit(WEXITSTATUS(exit_code));
}

int	handler(t_msh *list, int if_exit, t_env **env)
{
	int	exit_code;

	exit_code = 0;
	if (list->type == PIPE)
		piping(list, if_exit, env);
	else if (list->type == CMD)
		exec_cmd(list, env);
	else if (list->type == INFILE)
		exit_code = exec_infile(list, if_exit, env);
	else if (list->type == OUTFILE)
		exit_code = exec_outfile(list, if_exit, env);
	else if (list->type == APPEND)
		exit_code = exec_append(list, if_exit, env);
	else if (list->type == HEREDOC)
		exit_code = exec_heredoc(list, if_exit, env);
	else if (list->type == BUILTIN)
		exit_code = exec_builtin(list, if_exit, env);
	return (exit_code);
}

int	pre_exec(t_msh *list, t_env **env)
{
	t_msh	*curr;
	int		exit_code;

	exit_code = 0;
	curr = list;
	while (curr->left != NULL)
	{
		if (curr->type == PIPE || curr->type == CMD)
			return (-1);
		curr = curr->left;
	}
	if (curr->type == PIPE || curr->type == CMD)
		return (-1);
	if (curr->type == BUILTIN)
	{
		exit_code = handler(list, BUILTIN, env);
		dup2(curr->stdout_cpy, STDOUT_FILENO);
		dup2(curr->stdin_cpy, STDIN_FILENO);
		return (exit_code);
	}
	return (-1);
}

void	ctrl_c_in_child(int signal)
{
	(void)signal;
	exit(0);
}

int	minishell_exec(t_msh *list, t_env **env)
{
	int	exit_code;
	int	pid;

	exit_code = 0;
	if (list == NULL)
		return (-1);
	if (list->type != PIPE)
	{
		exit_code = pre_exec(list, env);
		if (exit_code > -1)
			return (exit_code);
	}
	pid = fork();
	if (pid < 0)
	{
		write(2, "ERROR FORK\n", 12);
		exit(1);
	}
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ctrl_c_in_child);
		exit_code = handler(list, CMD, env);
	}
	waitpid(pid, &exit_code, 0);
	exit_code = WEXITSTATUS(exit_code);
	return (exit_code);
}
