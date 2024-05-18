/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:49:59 by psanger           #+#    #+#             */
/*   Updated: 2024/05/13 20:43:37 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	wordcount(char *argv, char c)
{
	int		i;
	int		num;
	int		new_word;
	char	quote;

	new_word = 1;
	i = 0;
	num = 0;
	while (argv[i] != '\0')
	{
		while (argv[i] == c)
		{
			new_word = 1;
			i++;
		}
		if (argv[i] != '\0' && new_word == 1)
			num++;
		while (argv[i] != '\0' && argv[i] != c)
		{
			if (argv[i] =='\'' || argv[i] == '\"')
			{
				quote = argv[i];
				i++;
				while (argv[i] != quote)
					i++;
			}
			i++;
		}
		new_word = 0;
	}
	return (num);
}


char	**split_with_quotes(char *argv, char c)
{
	int		i = 0;
	int		j = 0;
	int		k = 0;
	char	quote = 0;
	char	**split;
	int		wc;

	wc = wordcount(argv, c);
	split = (char **)malloc(sizeof(char *) * (wc + 1));
	while (argv[i] != '\0')
	{
		while (argv[i] != '\0' && argv[i] == c)
			i++;
		if (j == 0)
			j = i;
		while (argv[i] != '\0' && argv[i] != c)
		{
			if (argv[i] == '\'' || argv[i] == '\"')
			{
				quote = argv[i];
				i++;
				while (argv[i] != quote)
					i++;
			}
			i++;
		}
		if (i > j && argv[i] != '\'' && argv[i] != '\"')
		{
			split[k] = ft_substr(argv, j, i - j);
			j = 0;
			k++;
		}
	}
	split[k] = NULL;
	return (split);
}

