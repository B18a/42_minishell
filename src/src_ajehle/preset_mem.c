/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preset_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:19:53 by ajehle            #+#    #+#             */
/*   Updated: 2024/04/05 15:33:36 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	preset_struct(t_minishell *lst)
{
	if(lst)
	{
		lst->next = NULL;
		lst->type = 0;
		if(lst->value)
		{
			lst->value->buildin = NULL;
			lst->value->cmd = NULL;
			lst->value->cmd_args = NULL;
			lst->value->name = NULL;
			lst->value->exec = FALSE;
			lst->value->error = FALSE;
		}
	}
}
