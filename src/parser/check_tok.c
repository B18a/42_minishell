/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:31:02 by psanger           #+#    #+#             */
/*   Updated: 2024/05/23 22:42:08 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_tok(t_tok **tok)
{
	t_tok	*curr;

	curr = *tok;
	if (!curr)
		return ;
	while (curr != NULL)
	{
		if (curr->type == PIPE)
		{
			if (curr->next == NULL || curr->next->type == PIPE)
			{
				free_mem(*tok);
				*tok = NULL;
				printf("syntax error\n");
				return ;
			}
		}
		curr = curr->next;
	}
	return ;
}
