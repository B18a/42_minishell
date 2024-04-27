/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:54:31 by ajehle            #+#    #+#             */
/*   Updated: 2024/04/25 10:59:22 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_args(char	**args)
{
	int	i;

	i = 0;
	if(args)
	{
		while(args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
	}
}

void	free_tree(t_msh *root)
{
	if(!root)
		return;
	if(root->cmd_path)
		free(root->cmd_path);
	if(root->cmd_args)
		free_args(root->cmd_args);
	free_tree(root->left);
	free_tree(root->right);
	free(root);
	return;
}
