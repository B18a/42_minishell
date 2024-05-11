/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:58:16 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/02 16:42:25 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_msh	*parsing(t_tok *tok)
{
	int		pipes_total;
	t_msh	*root;

	root = NULL;
	pipes_total = get_pipes(tok);
	printf("ANZAHL pipes_total:%i\n", pipes_total);
	if (pipes_total == 0)
	{
		root = fill_without_pipe(tok);
		root = sort_tree_without_pipe(root);
	}
	else if (pipes_total >= 1)
	{
		root = fill_with_pipes(tok, pipes_total);
		sort_tree_with_pipes(root, pipes_total);
	}
	printf("END OF PARSING\n\n");
	if (tok)
		free_mem(tok);
	return (root);
}
