/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:05:10 by psanger           #+#    #+#             */
/*   Updated: 2024/05/24 21:30:18 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_heredoc(t_msh *list, int if_exit, t_env **env)
{
	if (list == NULL)
	{
		write(2, "ERROR, PROBLEM WITH LIST\n", 26);
		mid_free_exit(1, env, NULL);
	}
	if (dup2(list->pipe_heredoc[0], STDIN_FILENO) < 0)
		exit(1);
	close (list->pipe_heredoc[0]);
	return (handler(list->left, if_exit, env, list->root));
}
