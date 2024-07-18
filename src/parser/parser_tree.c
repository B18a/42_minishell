/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:31:55 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/24 20:39:05 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_new(t_msh *new)
{
	new->cmd_args = NULL;
	new->cmd_path = NULL;
	new->left = NULL;
	new->right = NULL;
	new->stdin_cpy = 0;
	new->stdout_cpy = 0;
	new->pipe_heredoc[0] = 0;
	new->pipe_heredoc[1] = 0;
	new->root = NULL;
}

t_msh	*create_new(int type, char *content, t_env **env)
{
	t_msh	*new;

	new = NULL;
	new = (t_msh *)malloc(sizeof(t_msh));
	if (!new)
		return (NULL);
	init_new(new);
	new->type = type;
	if (content)
	{
		new->cmd_args = malloc(sizeof(char *) * 2);
		new->cmd_args[0] = ft_strdup(content);
		new->cmd_args[1] = NULL;
		if (type == CMD && new->cmd_args)
			new->cmd_path = get_path(new->cmd_args[0], env);
	}
	if (new->type == HEREDOC || new->type == BUILTIN)
	{
		new->stdin_cpy = dup(STDIN_FILENO);
		new->stdout_cpy = dup(STDOUT_FILENO);
	}
	return (new);
}

t_msh	*make_branch(t_tok **tok, t_env **env)
{
	t_msh	*branch;

	branch = NULL;
	if (tok)
	{
		branch = create_new((*tok)->type, (*tok)->content, env);
		(*tok) = (*tok)->next;
	}
	return (branch);
}
