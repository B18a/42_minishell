/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:05:44 by ajehle            #+#    #+#             */
/*   Updated: 2024/04/27 13:09:58 by ajehle           ###   ########.fr       */
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

// t_tok	*sort_tokens(t_tok *tok)
// {
// 	t_tok *start;
// 	t_tok *prev;

// 	start = tok;
// 	prev = NULL;
// 	while(tok && tok->next)
// 	{
// 		if(!is_redirect(tok->type) && is_redirect(tok->next->type) && tok->type != PIPE)
// 		{
// 			if(!prev)
// 			{
// 				start = tok->next;
// 				tok->next = start->next;
// 				start->next = tok;
// 			}
// 			else if(prev)
// 			{
// 				prev->next = tok->next;
// 				tok->next = tok->next->next;
// 				prev->next->next = tok;
// 			}
// 			tok = start;
// 		}
// 		prev = tok;
// 		tok = tok->next;
// 	}
// 	return (start);
// }

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
			ft_print_tok(tok);
			printf("------\n");
			handle_tokens(tok);
			ft_print_tok(tok);
			printf("------\n");
			// tok = sort_tokens(tok);
			// expander(tok);
			root = parsing(tok);
			if(root)
			{
				printf("------------------\n\n\n\n\n");
				print_tree(root);
				printf("------------------\n\n\n\n\n");
				minishell_exec(root);
				// sleep(1);
				free_tree(root);
			}
			free(line);
			if (tok)
				free_mem(tok);
			// running = 0;
		}
		return;
	}
}
