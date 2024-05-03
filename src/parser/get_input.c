/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:05:44 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/03 15:26:59 by psanger          ###   ########.fr       */
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

void	handle_tokens(t_tok *tok)
{
	while (tok)
	{
		if (tok->type == DQUOTE || tok->type == QUOTE)
		{
			// expanden?
		}
		else if (tok->type == ARG)
		{
			if (!ft_strncmp(tok->content, "$?\n", 3))
			{
				// ?????????????????
				printf("ARG IS $?\n");
				tok->type = CMD;
			}
			else if (check_for_buildins(tok->content))
			{
				printf("ARG IS BUILDIN\n");
				tok->type = BUILTIN;
			}
			else
			{
				tok->type = CMD;
			}
		}
		tok = tok->next;
	}
}

void	get_input(t_env **env)
{
	t_tok	*tok;
	t_msh	*root;
	char	*line;

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
			handle_tokens(tok);
			// ft_print_tok(tok);
			// printf("------\n");
			// expander(tok);
			root = parsing(tok);
			if (root)
			{
				printf("------------------\n\n\n\n\n");
				print_tree(root);
				printf("------------------\n\n\n");
				minishell_exec(root, env);
				free_tree(root);
			}
			free(line);
			rl_on_new_line();
		}
	}
}

