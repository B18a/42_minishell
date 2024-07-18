/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:10:04 by psanger           #+#    #+#             */
/*   Updated: 2024/05/24 21:30:44 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_infile(t_msh *list, int if_exit, t_env **env)
{
	int	fd;

	if (list == NULL)
	{
		write(2, "ERROR, PROBLEM WITH LIST\n", 26);
		mid_free_exit(1, env, NULL);
	}
	fd = open(list->cmd_args[0], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		if (if_exit == CMD)
			mid_free_exit(1, env, list->root);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		exit(1);
	close(fd);
	return (handler(list->left, if_exit, env, list->root));
}
