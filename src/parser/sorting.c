/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:20:13 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/02 16:29:50 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	swap_begin_of_tree(t_msh **start, t_msh **root)
{
	*start = (*root)->left;
	(*root)->left = (*start)->left;
	(*start)->left = *root;
}

void	swap_mid_of_tree(t_msh **prev, t_msh **root)
{
	(*prev)->left = (*root)->left;
	(*root)->left = (*root)->left->left;
	(*prev)->left->left = (*root);
}

t_msh	*sort_tree_without_pipe(t_msh *root)
{
	t_msh	*start;
	t_msh	*prev;

	start = root;
	prev = NULL;
	while (root && root->left)
	{
		if (!is_redirect(root->type) && is_redirect(root->left->type)
			&& root->type != PIPE)
		{
			if (!prev)
			{
				swap_begin_of_tree(&start, &root);
				// start = root->left;
				// root->left = start->left;
				// start->left = root;
			}
			else if (prev)
			{
				swap_mid_of_tree(&prev, &root);
				// prev->left = root->left;
				// root->left = root->left->left;
				// prev->left->left = root;
			}
			root = start;
		}
		prev = root;
		root = root->left;
	}
	return (start);
}

void	sort_tree_with_pipes(t_msh *root, int pipes_total)
{
	int		i;
	t_msh	*next;

	i = 0;
	next = root;
	while (i < pipes_total)
	{
		next->left = sort_tree_without_pipe(next->left);
		next = next->right;
		i++;
	}
	if (i == pipes_total)
		next->right = sort_tree_without_pipe(next->right);
}
