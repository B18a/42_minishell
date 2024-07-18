/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:58:16 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/24 00:13:42 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_msh	*parsing(t_tok *tok, t_env **env)
{
	int		pipes_total;
	t_msh	*root;

	if (tok == NULL)
		return (NULL);
	root = NULL;
	pipes_total = get_pipes(tok);
	if (pipes_total == 0)
	{
		root = fill_without_pipe(tok, env);
		root = sort_tree_without_pipe(root);
	}
	else if (pipes_total >= 1)
	{
		root = fill_with_pipes(tok, pipes_total, env);
		sort_tree_with_pipes(root, pipes_total, root, NULL);
	}
	if (!root)
		return (NULL);
	return (root);
}
