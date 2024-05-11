/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:05:10 by psanger           #+#    #+#             */
/*   Updated: 2024/05/10 10:58:16 by ajehle           ###   ########.fr       */
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
	char *temp = list->cmd_args[0];
	char *del = ft_strjoin(temp, "\n");
	write(list->stdout_cpy, "> ", 2);
	buffer = get_next_line(list->stdin_cpy);
	buffer = ft_expand(buffer, env, DQUOTE);
	while (ft_strncmp(buffer, del, ft_strlen(del) + 1) != 0)
	{
		write(list->stdout_cpy, "> ", 2);
		ft_putstr_fd(buffer, pfd[1]);
		free(buffer);
		buffer = get_next_line(STDIN_FILENO);
		buffer = ft_expand(buffer, env, DQUOTE);
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
