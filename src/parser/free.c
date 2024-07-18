/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:54:31 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/23 21:22:17 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_mem(t_tok *tok)
{
	if (tok)
	{
		if (tok->next)
			free_mem(tok->next);
		if (tok->content)
		{
			free(tok->content);
			tok->content = NULL;
		}
		free(tok);
		tok = NULL;
	}
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (args != NULL)
	{
		while (args[i] != NULL)
		{
			free(args[i]);
			args[i] = NULL;
			i++;
		}
		free(args);
		args = NULL;
	}
}

void	free_tree(t_msh *root)
{
	if (!root)
		return ;
	if (root->left != NULL)
		free_tree(root->left);
	if (root->right != NULL)
		free_tree(root->right);
	if (root->type == BUILTIN)
	{
		close(root->stdin_cpy);
		close(root->stdout_cpy);
	}
	if (root->cmd_path)
	{
		free(root->cmd_path);
		root->cmd_path = NULL;
	}
	if (root->cmd_args)
	{
		free_args(root->cmd_args);
		root->cmd_args = NULL;
	}
	free(root);
	root = NULL;
	return ;
}
