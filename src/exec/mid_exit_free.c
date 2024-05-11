/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mid_exit_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 21:09:44 by psanger           #+#    #+#             */
/*   Updated: 2024/05/10 22:27:38 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	mid_free_exit(int exit_code, t_env **env, t_msh *root)
{
	if(root)
		free_tree(root);
	if(env)
		env_free(*env);
	exit(exit_code);
}
