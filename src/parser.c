/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:58:16 by ajehle            #+#    #+#             */
/*   Updated: 2024/04/20 13:55:24 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_msh	*create_new(int type, char *content)
{
	t_msh	*new;

	new = NULL;
	new = (t_msh *)malloc(sizeof(t_msh));
	if (!new)
	{
		printf("Allocation create_new failed\n");
		return (NULL);
	}
	new->type = type;
	if (content)
	{
		new->cmd_args = ft_split(content, ' ');
		if ((type == BUILDIN || type == CMD) && new->cmd_args)
			new->cmd_path = get_path(new->cmd_args[0]);
	}
	else
		new->cmd_path = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_msh	*make_branch(t_tok **tok)
{
	t_msh	*branch;

	branch = NULL;
	if (tok && *tok)
	{
		if (is_redirect((*tok)->type))
		{
			if ((*tok)->next)
			{
				branch = create_new((*tok)->type, (*tok)->next->content);
				*tok = (*tok)->next->next;
			}
			else
				printf("Synatx error\n");
		}
		else if ((*tok)->type == CMD || (*tok)->type == BUILDIN)
		{
			branch = create_new((*tok)->type, (*tok)->content);
			// check for branch and for get path???
			*tok = (*tok)->next;
		}
	}
	if (branch == NULL)
		printf("make branch - failed\n");
	return (branch);
}

t_msh	*fill_without_pipe(t_tok *tok)
{
	t_msh	*new;
	t_msh	*root;
	t_msh	*temp;

	if (tok == NULL)
		return (NULL);
	root = make_branch(&tok);
	temp = root;
	while (root && tok)
	{
		new = make_branch(&tok);
		while (temp->left)
			temp = temp->left;
		temp->left = new;
	}
	return (root);
}

t_msh	*create_pipes(int pipes)
{
	t_msh	*root;
	t_msh	*temp;
	t_msh	*new;
	int		i;

	i = 0;
	root = create_new(PIPE, "NULL");
	// check is missing -> free
	temp = root;
	while (i < pipes - 1)
	{
		new = create_new(PIPE, "NULL");
		// check is missing -> free
		temp->right = new;
		temp = new;
		i++;
	}
	return (root);
}

t_msh	*fill_with_pipes(t_tok *tok, int pipes_total)
{
	t_msh	*new;
	t_msh	*root;
	t_msh	*temp;
	t_msh	*last_pipe;
	int		pipe;

	pipe = 0;
	root = create_pipes(pipes_total);
	if (!root)
	{
		printf("fill with pipes - root is NULL\n");
		return (NULL);
	}
	temp = root;
	last_pipe = root;
	while (tok && pipe < pipes_total)
	{
		if (tok->type == PIPE)
		{
			pipe++;
			if (pipe < pipes_total)
			{
				last_pipe = last_pipe->right;
				temp = last_pipe;
			}
			tok = tok->next;
		}
		else
		{
			new = make_branch(&tok);
			if (!new)
			{
				printf("new is NULL\n");
				return (NULL);
			}
			temp->left = new;
			temp = new;
		}
	}
	if (tok && pipe == pipes_total)
	{
		printf("PIPE %i, PIPES TOTAL %i\n", pipe, pipes_total);
		new = make_branch(&tok);
		if (!new)
		{
			printf("fill with pipes - new is NULL\n");
			return (root);
		}
		last_pipe->right = new;
		temp = new;
	}
	while (tok)
	{
		new = make_branch(&tok);
		if (!new)
		{
			printf("Last new is NULL\n");
			return (NULL);
		}
		temp->left = new;
		temp = new;
	}
	return (root);
}

t_msh	*parsing(t_tok *tok)
{
	int		pipes_total;
	t_msh	*root;

	root = NULL;
	pipes_total = get_pipes(tok);
	printf("ANZAHL pipes_total:%i\n", pipes_total);
	if (pipes_total == 0)
		root = fill_without_pipe(tok);
	else if (pipes_total >= 1)
		root = fill_with_pipes(tok, pipes_total);
	printf("END OF PARSING\n\n");
	return (root);
}
