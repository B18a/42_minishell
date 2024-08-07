/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:37:08 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/23 21:32:36 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_msh	*create_pipes(int pipes, t_env **env)
{
	t_msh	*root;
	t_msh	*temp;
	t_msh	*new;
	int		i;

	i = 0;
	root = create_new(PIPE, "NULL", env);
	if (!root)
		return (NULL);
	temp = root;
	while (i < pipes - 1)
	{
		new = create_new(PIPE, "NULL", env);
		if (!new)
			return (free_tree(root), NULL);
		temp->right = new;
		temp = new;
		i++;
	}
	return (root);
}

t_msh	*make_else(t_tok **tok, t_msh *temp, t_msh **dst, t_env **env)
{
	t_msh	*new;

	new = make_branch(tok, env);
	if (!new)
		return (NULL);
	*dst = new;
	temp = new;
	return (temp);
}

void	handle_pipe(int *pipes_total, t_tok **tok, t_msh **temp,
		t_msh **last_pipe)
{
	(*pipes_total)--;
	if (*pipes_total)
	{
		*last_pipe = (*last_pipe)->right;
		*temp = *last_pipe;
	}
	*tok = (*tok)->next;
}

t_msh	*fill_with_pipes(t_tok *tok, int pipes_total, t_env **env)
{
	t_msh	*root;
	t_msh	*temp;
	t_msh	*last_pipe;

	root = create_pipes(pipes_total, env);
	if (!root)
		return (NULL);
	temp = root;
	last_pipe = root;
	while (tok && pipes_total)
	{
		if (tok->type == PIPE)
			handle_pipe(&pipes_total, &tok, &temp, &last_pipe);
		else
			temp = make_else(&tok, temp, &temp->left, env);
	}
	if (tok && pipes_total == 0)
		temp = make_else(&tok, temp, &last_pipe->right, env);
	while (tok)
		temp = make_else(&tok, temp, &temp->left, env);
	return (root);
}
