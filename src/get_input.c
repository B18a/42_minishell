/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:05:44 by ajehle            #+#    #+#             */
/*   Updated: 2024/04/20 13:53:20 by ajehle           ###   ########.fr       */
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
	char	*buildins[] ={"exit", "env", "unset", "export", "pwd", "cd", "echo"};
	int		i;

	i = 0;
	while(i < 7)
	{
		if(!ft_strncmp(str,buildins[i], ft_strlen(buildins[i])))
			return(1);
		i++;
	}
	return(0);
}

void	handle_tokens(t_tok *tok)
{
	while (tok)
	{
		if (tok->type == ARG)
		{

			if (!ft_strncmp(tok->content, "$?\n", 3))
			{
				printf("ARG IS $?\n");
				tok->type = CMD;
			}
			else if (check_for_buildins(tok->content))
			{
				printf("ARG IS BUILDIN\n");
				tok->type = BUILDIN;
			}
			else
			{
				tok->type = CMD;
			}
		}
		tok = tok->next;
	}
}

void	get_input(void)
{
	t_tok	*tok;
	t_msh	*root;
	char	*line;
	int		running;

	tok = NULL;
	root = NULL;
	line = NULL;
	running = 1;
	while (running)
	{
		line = readline("minishell:");
		if (line)
		{
			add_history(line);
			tok = tokenizer(line);
			handle_tokens(tok);
			ft_print_tok(tok);
			// expander(tok);
			root = parsing(tok);
			print_tree(root);
			free(line);
			if (tok)
				free_mem(tok);
		}
	}
}
