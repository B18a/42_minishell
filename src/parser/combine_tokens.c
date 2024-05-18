/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:27:30 by psanger           #+#    #+#             */
/*   Updated: 2024/05/16 13:28:26 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"

// int	join_size(char **s)
// {
// 	int	i;

// 	if (s == NULL)
// 		return (0);
// 	i = 0;
// 	while (s[i] != NULL)
// 		i++;
// 	return (i);
// }

// void	free_token(t_tok_ps *tok)
// {
// 	int	i;

// 	i = 0;
// 	tok->type = 0;
// 	tok->syntax_error = 0;
// 	while (tok->content[i] != NULL)
// 	{
// 		free(tok->content[i]);
// 		i++;
// 	}
// 	free(tok->content);
// 	free(tok->next);
// }

// void	join_tokens(t_tok_ps *to_join, t_tok_ps *prev, t_tok_ps *join_from)
// {
// 	int		size;
// 	char	**new_content;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	size = join_size(to_join->content) + join_size(join_from->content);
// 	new_content = (char **)malloc(sizeof(char *) * (size + 1));
// 	while (to_join->content[i] != NULL)
// 	{
// 		new_content[i] = malloc(sizeof(char) * (ft_strlen(to_join->content[i]) + 1));
// 		ft_strlcpy(new_content[i], to_join->content[i], ft_strlen(to_join->content[j]) + 1);
// 		i++;
// 	}
// 	while (join_from->content[j] != NULL)
// 	{
// 		new_content[i + j] = malloc(sizeof(char) * (ft_strlen(join_from->content[j]) + 1));
// 		ft_strlcpy(new_content[i + j], join_from->content[j], ft_strlen(join_from->content[j]) + 1);
// 		j++;
// 	}
// 	new_content[i + j] = NULL;
// 	prev->next = join_from->next;
// 	free_token(join_from);
// }

// void	combine_tokens(t_tok_ps *tok)
// {
// 	t_tok_ps	*previous_cmd_token;
// 	t_tok_ps	*previous_token;
// 	t_tok_ps	*curr;

// 	previous_cmd_token = NULL;
// 	previous_token = NULL;
// 	curr = tok;
// 	while (curr != NULL)
// 	{
// 		if (curr->type == CMD || curr->type == BUILTIN)
// 		{
// 			if (previous_cmd_token == NULL) {
// 				printf("%stest0\n%s", RED, RESET);
// 				previous_cmd_token = curr;
// 			}
// 			else
// 			{
// 				printf("%stest1\n%s", RED, RESET);
// 				while (curr != NULL && curr->type != PIPE)
// 				{
// 					if (curr->type == CMD || curr->type == BUILTIN)
// 						join_tokens(previous_cmd_token, previous_token, curr);
// 					previous_token = curr;
// 					curr = curr->next;
// 				}
// 				previous_cmd_token = NULL;
// 			}
// 		}
// 		printf("%stest2\n%s", BLUE, RESET);
// 		previous_token = curr;
// 		curr = curr->next;
// 	}

// }
