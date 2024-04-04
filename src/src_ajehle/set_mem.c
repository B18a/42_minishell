/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:22:09 by ajehle            #+#    #+#             */
/*   Updated: 2024/04/04 10:53:51 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_minishell	*set_mem_lst(void)
{
	t_minishell	*lst;

	lst = NULL;
	lst = malloc(sizeof(t_minishell));
	if(!lst)
		return(NULL);
	if(lst)
	{
		lst->value = NULL;
		lst->value = malloc(sizeof(t_value));
		if(!lst->value)
			return(NULL);
		preset_struct(lst);
	}
	return (lst);
}
