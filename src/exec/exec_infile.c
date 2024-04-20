/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:10:04 by psanger           #+#    #+#             */
/*   Updated: 2024/04/09 21:56:08 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_infile(t_minishell *list)
{
	if (list == NULL)
	{
		write(2, "ERROR, PROBLEM WITH LIST\n", 26);
		exit(1);
	}
	int fd = open(list->value->name, O_RDONLY);
	if (fd < 0) {
		printf("%s: No such file or directory\n", list->value->name);
		return ;
	}
	if (list->value->exec != TRUE)
		return ;
	if (dup2(fd, STDIN_FILENO) < 0)
		exit(1);
	close(fd);
	handler(list->left);
}
