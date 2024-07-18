/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_no_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:36:42 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/23 15:34:33 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_msh	*fill_without_pipe(t_tok *tok, t_env **env)
{
	t_msh	*new;
	t_msh	*root;
	t_msh	*temp;

	if (tok == NULL)
		return (NULL);
	root = make_branch(&tok, env);
	if (!root)
		return (NULL);
	temp = root;
	while (root && tok)
	{
		new = make_branch(&tok, env);
		if (!new)
			return (free_tree(root), NULL);
		while (temp->left)
			temp = temp->left;
		temp->left = new;
	}
	return (root);
}
