/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:20:13 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/11 09:46:57 by ajehle           ###   ########.fr       */
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
void	combine_token_cmd(t_msh **branch)
{
		t_msh	*cmd;
		t_msh	*prev;
		t_msh	*cur;
		char	*new;
		char	*old;
		int		i;
		int		flag = 0;;

		i = 0;
		cur = *branch;
		new = NULL;
		old = new;
		// if(cur && cur->type != CMD)
		if(cur && (cur->type != CMD || cur->type != BUILTIN))
			cur = cur->left;
		// if(cur && cur->type == CMD)
		if(cur && (cur->type == CMD || cur->type == BUILTIN))
			cmd = cur;
		// while(cur && cur->type == CMD)
		while(cur && (cur->type == CMD || cur->type == BUILTIN))
		{
			// printf("CMD |%s|\n",cur->cmd_args[0]);
			while(cur->cmd_args && cur->cmd_args[i])
			{
				new = ft_strjoin(old," ");
				free(old);
				old = new;
				new = ft_strjoin(old,cur->cmd_args[i]);
				free(old);
				old = new;
				i++;
			}
			i = 0;
			prev = cur;
			cur = cur->left;
			prev->left = NULL;
			flag = 1;
		// printf("TOKEN CMD NEW|%s|\n",new);
		}
		// printf("TOKEN CMD NEW|%s|\n",new);
		// // free(cmd->cmd_args);
		// cmd->cmd_args = NULL;
		if(flag)
			cmd->cmd_args = ft_split(new, ' ');
		// // free_tree(cmd->left);
		// cmd->left = NULL;
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
		}
		prev = root;
		root = root->left;
	}
															// print_tree(start);
	combine_token_cmd(&start);
															// print_tree(start);
	return (start);
}

void	sort_tree_with_pipes(t_msh *root, int pipes_total)
{
	int		i;
	t_msh	*next;
	t_msh	*prev;

	i = 0;
	if (root)
	{
		next = root;
		while (i < pipes_total)
		{
			next->left = sort_tree_without_pipe(next->left);
			next = next->right;
			i++;
		}
		if (i == pipes_total)
		{
			next = root;
			while (next->type == PIPE)
			{
				prev = next;
				next = next->right;
			}
			prev->right = sort_tree_without_pipe(prev->right);
		}
	}
}
