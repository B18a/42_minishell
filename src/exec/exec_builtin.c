/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:21:10 by psanger           #+#    #+#             */
/*   Updated: 2024/04/09 21:55:59 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_minishell *list)
{
	if (list == NULL) {
		write(2, "ERROR LIST\n", 12);
		exit (1);
	}
	if (ft_strncmp (list->value->buildin, "echo", 4) == 0) {
		printf("%s", list->value->name);
		exit(0);
	}
	exit(0);
}
