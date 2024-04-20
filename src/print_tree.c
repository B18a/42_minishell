/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:37:04 by ajehle            #+#    #+#             */
/*   Updated: 2024/04/20 13:55:37 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_tabs(int tabs)
{
	int	i;

	i = 0;
	while (i < tabs)
	{
		printf("\t");
		i++;
	}
}

void	print_tree_rec(t_msh *root, int level)
{
	if (root == NULL)
	{
		print_tabs(level);
		printf("---<empty>---\n");
		return ;
	}
	print_tabs(level);
	printf("TYPE:%s CONTENT:%s\n", return_true_type(root->type),root->cmd_args[0]);
	// printf("TYPE:%s \n", return_true_type(root->type));
	// printf("CONTENT:%s\n", root->cmd_args[0]);
	// printf("PATH:%s\n", root->cmd_path);
	// printf("CONTENT		:	\n");
	// print_2d_arr(root->cmd_args);
	print_tabs(level);
	printf("left\n");
	print_tree_rec(root->left, level + 1);
	print_tabs(level);
	printf("right\n");
	print_tree_rec(root->right, level + 1);
	print_tabs(level);
	printf("done\n");
}

void	print_tree(t_msh *root)
{
	print_tree_rec(root, 0);
	printf("\n");
}
