/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_no_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:36:42 by ajehle            #+#    #+#             */
/*   Updated: 2024/04/25 11:04:23 by ajehle           ###   ########.fr       */
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
	root = make_branch(&tok);
	if(!root)
	{
		printf("make branch root - empty\n");
		return(NULL);
	}
	temp = root;
	while (root && tok)
	{
		new = make_branch(&tok);
		if(!new)
		{
			printf("make branch new - empty\n");
			free_tree(root);
			return(NULL);
		}
		while (temp->left)
			temp = temp->left;
		temp->left = new;
	}
	return (root);
}
