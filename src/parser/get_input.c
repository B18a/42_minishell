/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:05:44 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/11 09:38:37 by ajehle           ###   ########.fr       */
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
			free(tok->content);
		free(tok);
	}
}

int	check_for_buildins(char *str)
{
	if (!ft_strncmp(str, "exit", 5))
		return (1);
	else if (!ft_strncmp(str, "env", 4))
		return (1);
	else if (!ft_strncmp(str, "unset", 6))
		return (1);
	else if (!ft_strncmp(str, "export", 7))
		return (1);
	else if (!ft_strncmp(str, "pwd", 4))
		return (1);
	else if (!ft_strncmp(str, "cd", 3))
		return (1);
	else if (!ft_strncmp(str, "echo", 5))
		return (1);
	return (0);
}

void	handle_tokens(t_tok *tok, int exit_code, t_env **env)
{
	while (tok)
	{
		if (tok->type == DQUOTE || tok->type == QUOTE)
		// {
			tok->content = ft_expand(tok->content, env, tok->type);
			// tok->type = CMD;
			// test for splitting!!!
		// }
		else if (tok->type == ARG)
		{
			if (!ft_strncmp(tok->content, "$?", 3))
			{
				tok->content = ft_itoa(exit_code);
				tok->type = CMD;
			}
			else if (check_for_buildins(tok->content))
			{
				tok->content = ft_expand(tok->content, env, tok->type);
				tok->type = BUILTIN;
			}
			else
			{
				tok->content = ft_expand(tok->content, env, tok->type);
				tok->type = CMD;
			}
		}
		tok = tok->next;
	}
}
// dollar darf kein einzelner token sein und muss im expander zum exit code verwandelt werden

void	add_root_node(t_msh *list, t_msh *root)
{
	if (!list)
		return ;
	list->root = root;
	if (root->cmd_args)
		add_root_node(list->left, root);
	add_root_node(list->right, root);
	return ;
}

void	get_input(t_env **env)
{
	t_tok	*tok;
	t_msh	*root;
	char	*line;
	int		exit_code;

	exit_code = 0;
	tok = NULL;
	root = NULL;
	line = NULL;
	while (1)
	{
		line = readline("minishell:");
		if (line == NULL)
			return ;
		if (line)
		{
			add_history(line);
			tok = tokenizer(line);
			handle_tokens(tok, exit_code, env);
														// ft_print_tok(tok);
			root = parsing(tok);
														// print_tree(root);
			add_root_node(root, root);
			if (root)
			{
				exit_code = minishell_exec(root, env);
				free_tree(root);
			}
			free(line);
			rl_on_new_line();
		}
	}
}
