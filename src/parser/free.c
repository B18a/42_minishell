/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:54:31 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/10 10:41:17 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (args != NULL)
	{
		while (args[i] != NULL)
		{
			free(args[i]);
			i++;
		}
		free(args);
	}
}

void	free_tree(t_msh *root)
{
	if (!root)
		return ;
	if (root->cmd_path)
		free(root->cmd_path);
	if (root->cmd_args)
		free_args(root->cmd_args);
	if (root->left != NULL)
		free_tree(root->left);
	if (root->right != NULL)
		free_tree(root->right);
	free(root);
	return ;
}
