/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:46:21 by ajehle            #+#    #+#             */
/*   Updated: 2024/04/27 12:13:51 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*return_true_type(int type)
{
	if (type == ARG)
		return ("ARG");
	if (type == QUOTE)
		return ("QUOTE");
	if (type == DQUOTE)
		return ("DQUOTE");
	if (type == REDIRECT)
		return ("REDIRECT");
	if (type == PIPE)
		return ("PIPE");
	if (type == CMD)
		return ("CMD");
	if (type == INFILE)
		return ("INFILE");
	if (type == OUTFILE)
		return ("OUTFILE");
	if (type == APPEND)
		return ("APPEND");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == BUILTIN)
		return ("BUILTIN");
	return ("WRONG TYPE!!!");
}

void	ft_print_tok(t_tok *tok)
{
	int	i;

	i = 0;
	printf("--------PRINT tok:-------------\n");
	while (tok)
	{
		printf("ELEMENT	NBR	:	%i\n", i);
		printf("TYPE		:	%s\n", return_true_type(tok->type));
		printf("CONTENT		:	%s\n", tok->content);
		printf("-------------------------------------------\n");
		tok = tok->next;
		i++;
	}
}

void	print_2d_arr(char **arr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (arr)
	{
		while (arr[i])
		{
			printf("				[%i]	", i);
			while (arr[i][j])
			{
				printf("%c", arr[i][j]);
				j++;
			}
			printf("\n");
			j = 0;
			i++;
		}
	}
	else
		printf("(null)\n");
}
