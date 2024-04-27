/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:58:16 by ajehle            #+#    #+#             */
/*   Updated: 2024/04/27 12:57:30 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


t_msh	*sort_tree_without_pipe(t_msh *root)
{
	t_msh *start;
	t_msh *prev;

	start = root;
	prev = NULL;
	while(root && root->left)
	{
		if(!is_redirect(root->type) && is_redirect(root->left->type) && root->type != PIPE)
		{
			if(!prev)
			{
				start = root->left;
				root->left = start->left;
				start->left = root;
			}
			else if(prev)
			{
				prev->left = root->left;
				root->left = root->left->left;
				prev->left->left = root;
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
	int	i;

	i = 0;
	t_msh	*next;
	next = root;
	while(i < pipes_total)
	{
		next->left = sort_tree_without_pipe(next->left);
		next = next->right;
		i++;
	}
	if(i == pipes_total)
		next->right = sort_tree_without_pipe(next->right);
}



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
	return (root);
}
