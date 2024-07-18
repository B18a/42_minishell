/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_input_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:58:14 by psanger           #+#    #+#             */
/*   Updated: 2024/05/22 16:10:50 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	len_in_quotes(int *i, int *len, char *argv)
{
	char	quote;

	quote = 0;
	quote = argv[*i];
	*i += 1;
	*len += 1;
	while (argv[*i] != quote)
	{
		*i += 1;
		*len += 1;
	}
	*i += 1;
	*len += 1;
}

void	len_is_special(int *i, int *len, char *argv)
{
	char	temp;

	temp = 0;
	if (*i > 0)
	{
		if (argv[*i - 1] != ' ')
			*len += 1;
	}
	temp = argv[*i];
	*i += 1;
	if (argv[*i] == temp && temp != '|')
	{
		*len += 1;
		*i += 1;
	}
	*len += 2;
}

void	is_whitespace(int *i, int *len, char *argv)
{
	*len += 1;
	while (argv[*i] == ' ')
		*i += 1;
}

int	input_len(char *argv)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] == ' ')
			is_whitespace(&i, &len, argv);
		else if (argv[i] == '\'' || argv[i] == '\"')
			len_in_quotes(&i, &len, argv);
		else if (is_special(argv[i]) == 1 && argv[i + 1] != ' ')
			len_is_special(&i, &len, argv);
		else
		{
			i++;
			len++;
		}
		if (argv[i] == '\0')
			return (len);
	}
	return (len);
}
