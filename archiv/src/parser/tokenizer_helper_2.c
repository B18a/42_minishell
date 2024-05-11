/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helper_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:46:24 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/02 16:28:51 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_space(char c)
{
	if (c && c == ' ')
		return (1);
	return (0);
}

int	skip_spaces(char *argv, int i)
{
	while (argv[i] && argv[i] == ' ')
		i++;
	return (i);
}

int	is_special_char(char c)
{
	if (c == 34 || c == 39 || c == '|' || c == '>' || c == '<' || is_space(c))
		return (1);
	else
		return (0);
}

int	is_unique_quote(char c)
{
	if (c == 34)
		return (DQUOTE);
	else if (c == 39)
		return (QUOTE);
	else
		return (0);
}

int	is_unique_char(char c)
{
	if (c == 34)
		return (QUOTE);
	else if (c == 39)
		return (DQUOTE);
	else if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (INFILE);
	else if (c == '>')
		return (OUTFILE);
	else
		return (0);
}
