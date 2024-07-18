/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mid_exit_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 21:09:44 by psanger           #+#    #+#             */
/*   Updated: 2024/05/21 19:48:39 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	mid_free_exit(int exit_code, t_env **env, t_msh *root)
{
	if (root)
		free_tree(root);
	if (env)
		env_free(*env);
	exit (exit_code);
}
