/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:49:59 by psanger           #+#    #+#             */
/*   Updated: 2024/05/24 22:04:42 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	contains_char(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	wordcount_helper(char *argv, char *c, int *count)
{
	while (contains_char(argv[count[0]], c) == 1)
	{
		count[2] = 1;
		count[0]++;
	}
	if (argv[count[0]] != '\0' && count[2] == 1)
		count[1]++;
}

int	wordcount(char *argv, char *c)
{
	char	quote;
	int		count[3];

	init_counters(count, 0, 0, 1);
	while (argv[count[0]] != '\0')
	{
		wordcount_helper(argv, c, count);
		while (argv[count[0]] != '\0' && contains_char(argv[count[0]], c) != 1)
		{
			if (argv[count[0]] == '\'' || argv[count[0]] == '\"')
			{
				quote = argv[count[0]];
				count[0]++;
				while (argv[count[0]] != quote)
					count[0]++;
			}
			count[0]++;
		}
		count[2] = 0;
	}
	return (count[1]);
}

void	split_with_quotes_helper(char *argv, int *i)
{
	char	quote;

	if (argv[*i] == '\'' || argv[*i] == '\"')
	{
		quote = argv[*i];
		(*i)++;
		while (argv[*i] != quote)
			(*i)++;
	}
	(*i)++;
}

char	**split_with_quotes(char *argv, char *c)
{
	int		i;
	int		j;
	int		k;
	char	**split;

	i = 0;
	j = 0;
	k = 0;
	split = (char **)malloc(sizeof(char *) * (wordcount(argv, c) + 1));
	while (argv[i] != '\0')
	{
		while (argv[i] != '\0' && contains_char(argv[i], c))
			i++;
		if (j == 0)
			j = i;
		while (argv[i] != '\0' && contains_char(argv[i], c) != 1)
			split_with_quotes_helper(argv, &i);
		if (i > j && argv[i] != '\'' && argv[i] != '\"')
		{
			split[k++] = ft_substr(argv, j, i - j);
			j = 0;
		}
	}
	split[k] = NULL;
	return (split);
}
