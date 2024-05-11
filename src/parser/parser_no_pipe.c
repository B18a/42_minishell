/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_no_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:36:42 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/10 16:17:02 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_msh	*fill_without_pipe(t_tok *tok)
{
	t_msh	*new;
	t_msh	*root;
	t_msh	*temp;

	if (tok == NULL)
		return (NULL);
	if ((ft_strncmp(tok->content, "", 1) == 0))
		tok = tok->next;
	root = make_branch(&tok);
	if (!root)
		return (NULL);
	temp = root;
	while (root && tok)
	{
		new = make_branch(&tok);
		if (!new)
			return (free_tree(root), NULL);
		while (temp->left)
			temp = temp->left;
		temp->left = new;
	}
	return (root);
}
