/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:05:10 by psanger           #+#    #+#             */
/*   Updated: 2024/05/17 13:29:20 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_heredoc(t_msh *list, int if_exit, t_env **env)
{
	int		pfd[2];
	char	*buffer;
	char	*temp;
	char	*del;

	if (list == NULL)
	{
		write(2, "ERROR LIST\n", 12);
		exit(1);
	}
	if (pipe(pfd) < 0)
	{
		write(2, "ERROR PIPE HEREDOC\n", 20);
		exit(1);
	}
	buffer = NULL;
	temp = list->cmd_args[0];
	del = ft_strjoin(temp, "\n");
	write(list->stdout_cpy, "> ", 2);
	buffer = get_next_line(list->stdin_cpy);
	buffer = ft_expand(buffer, env, DQUOTE, 0);
	while (ft_strncmp(buffer, del, ft_strlen(del) + 1) != 0)
	{
		write(list->stdout_cpy, "> ", 2);
		ft_putstr_fd(buffer, pfd[1]);
		free(buffer);
		buffer = get_next_line(STDIN_FILENO);
		buffer = ft_expand(buffer, env, DQUOTE, 0);
	}
	if (buffer != NULL)
		free(buffer);
	close(pfd[p_write]);
	if (dup2(pfd[p_read], STDIN_FILENO) < 0)
	{
		write(2, "DUP2 ERROR HEREDOC\n", 20);
		exit(1);
	}
	close(pfd[p_read]);
	return (handler(list->left, if_exit, env));
}
