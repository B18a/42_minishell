/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:20:13 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/24 00:14:00 by psanger          ###   ########.fr       */
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

void	combine_token_cmd(t_msh *branch)
{
	t_msh	*cmd;
	t_msh	*cur;

	cur = branch;
	while (cur && cur->type != CMD && cur->type != BUILTIN)
		cur = cur->left;
	if (cur == NULL)
		return ;
	if (cur && (cur->type == CMD || cur->type == BUILTIN))
		cmd = cur;
	cur = cur->left;
	while (cur && (cur->type == CMD || cur->type == BUILTIN))
	{
		cmd->cmd_args = join_two_d_arr(cmd->cmd_args, cur->cmd_args);
		cur = cur->left;
	}
	if (cmd->left != NULL)
	{
		free_tree(cmd->left);
		cmd->left = NULL;
	}
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
				swap_begin_of_tree(&start, &root);
			else if (prev)
				swap_mid_of_tree(&prev, &root);
			root = start;
			prev = NULL;
		}
		else
		{
			prev = root;
			root = root->left;
		}
	}
	combine_token_cmd(start);
	return (start);
}

void	sort_tree_with_pipes(t_msh *root, int pipes_total, t_msh *next,
		t_msh *prev)
{
	int	i;

	i = 0;
	if (root)
	{
		while (i < pipes_total)
		{
			next->left = sort_tree_without_pipe(next->left);
			next = next->right;
			i++;
		}
		if (i == pipes_total)
		{
			next = root;
			while (next && next->type == PIPE)
			{
				prev = next;
				next = next->right;
			}
			if (prev && prev->right)
				prev->right = sort_tree_without_pipe(prev->right);
		}
	}
}
