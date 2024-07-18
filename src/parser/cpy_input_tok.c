/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_input_tok.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:05:53 by psanger           #+#    #+#             */
/*   Updated: 2024/05/24 13:03:34 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cpy_argv_input(int *i, int *j, char *argv, char *input)
{
	input[*j] = argv[*i];
	*j += 1;
	*i += 1;
}

void	cpy_special_char(int *i, int *j, char *argv, char *input)
{
	char	temp;

	temp = 0;
	if (*i > 0)
	{
		if (argv[*i - 1] != ' ')
		{
			input[*j] = ' ';
			*j += 1;
		}
	}
	temp = argv[*i];
	cpy_argv_input(i, j, argv, input);
	if (argv[*i] == temp && temp != '|')
		cpy_argv_input(i, j, argv, input);
	if (argv[*i] != '\0' && argv[*i] != ' ')
	{
		input[*j] = ' ';
		*j += 1;
	}
}

void	cpy_in_quotes(int *i, int *j, char *argv, char *input)
{
	char	quote;

	quote = 0;
	quote = argv[*i];
	cpy_argv_input(i, j, argv, input);
	while (argv[*i] != quote)
		cpy_argv_input(i, j, argv, input);
	cpy_argv_input(i, j, argv, input);
}

void	cpy_skip_whitespace(int *i, int *j, char *argv, char *input)
{
	input[*j] = argv[*i];
	*j += 1;
	while (argv[*i] == ' ')
		*i += 1;
}

char	*cpy_input(char *argv, char *input)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] == ' ')
		{
			cpy_skip_whitespace(&i, &j, argv, input);
		}
		else if (is_special(argv[i]) == 1)
			cpy_special_char(&i, &j, argv, input);
		else if (argv[i] == '\'' || argv[i] == '\"')
			cpy_in_quotes(&i, &j, argv, input);
		else
			cpy_argv_input(&i, &j, argv, input);
	}
	input[j] = '\0';
	return (input);
}
