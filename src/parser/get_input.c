/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:05:44 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/24 18:45:02 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		{
			tok->content = ft_expand(tok->content, env, tok->type, exit_code);
			tok->type = CMD;
		}
		else if (tok->type == ARG)
		{
			if (check_for_buildins(tok->content))
			{
				tok->content = ft_expand(tok->content, env, tok->type,
						exit_code);
				tok->type = BUILTIN;
			}
			else
			{
				tok->content = ft_expand(tok->content, env, tok->type,
						exit_code);
				tok->type = CMD;
			}
		}
		tok = tok->next;
	}
}

void	add_root_node(t_msh *list, t_msh *root)
{
	if (list == NULL)
		return ;
	list->root = root;
	if (root && root->cmd_args)
		add_root_node(list->left, root);
	add_root_node(list->right, root);
	return ;
}

void	msh_loop(char *line, t_env **env, int *exit_code)
{
	t_msh	*root;
	t_tok	*tok;

	tok = NULL;
	root = NULL;
	if (ft_strncmp(line, "", 2) != 0)
		add_history(line);
	tok = tokenizer_psanger(line, env, exit_code);
	check_tok(&tok);
	root = parsing(tok, env);
	if (tok)
		free_mem(tok);
	if (root)
	{
		add_root_node(root, root);
		handle_heredoc(env, root, *exit_code);
		*exit_code = minishell_exec(root, env);
		free_tree(root);
		root = NULL;
	}
	rl_on_new_line();
}

int	get_input(t_env **env)
{
	char	*line;
	int		exit_code;

	exit_code = 0;
	line = NULL;
	while (1)
	{
		line = readline("minishell:");
		if (line == NULL)
		{
			printf("exit\n");
			return (1);
		}
		else if (line)
		{
			msh_loop(line, env, &exit_code);
		}
	}
	rl_clear_history();
}
