/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreasjehle <andreasjehle@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:05:10 by psanger           #+#    #+#             */
/*   Updated: 2024/05/05 17:40:56 by andreasjehl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_heredoc(t_msh *list, int if_exit, t_env **env)
{
	if (list == NULL) {
		write(2, "ERROR LIST\n", 12);
		exit(1);
	}
	int pfd[2];
	if (pipe(pfd) < 0) {
		write(2, "ERROR PIPE HEREDOC\n", 20);
		exit(1);
	}
	char *buffer = NULL;
	char *del = list->cmd_args[0];
	write(list->stdout_cpy, "> ", 2);
	buffer = get_next_line(list->stdin_cpy);
	while (ft_strncmp(buffer, del, ft_strlen(del) != 0)
			|| ft_strlen(buffer) - ft_strlen(del) != 1) {
		write(list->stdout_cpy, "> ", 2);
		ft_putstr_fd(buffer, pfd[1]);
		free(buffer);
		buffer = get_next_line(STDIN_FILENO);
	}
	if (buffer != NULL)
		free(buffer);
	close(pfd[p_write]);
	if (dup2(pfd[p_read], STDIN_FILENO) < 0) {
		write(2, "DUP2 ERROR HEREDOC\n", 20);
		exit(1);
	}
	close(pfd[p_read]);
	handler(list->left, if_exit, env);
}
