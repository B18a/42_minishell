/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_psanger.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:42:35 by psanger           #+#    #+#             */
/*   Updated: 2024/05/24 22:03:59 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_input(char *argv)
{
	char	quote;
	int		i;

	i = 0;
	quote = 0;
	while (argv[i] != '\0')
	{
		if (is_quote(argv[i]) != 0)
		{
			quote = argv[i];
			i++;
			while (argv[i] != '\0' && argv[i] != quote)
				i++;
			if (argv[i] == '\0')
			{
				printf("Open Quotes !?\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

char	**up_input(char *argv)
{
	char	*input;
	char	*res;
	char	**split;
	int		size;

	input = ft_strtrim(argv, " \t\n");
	free(argv);
	size = input_len(input);
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	res = cpy_input(input, res);
	free(input);
	split = split_with_quotes(res, " \t\n");
	free(res);
	return (split);
}

void	free_input(char **input)
{
	int	i;

	i = 0;
	while (input[i] != NULL)
	{
		free(input[i]);
		input[i] = NULL;
		i++;
	}
	free(input);
}

t_tok	*tokenizer_psanger(char *argv, t_env **env, int *exit_code)
{
	char	**input;
	t_tok	*tok;

	input = NULL;
	tok = NULL;
	if (check_input(argv) == 1)
		return (NULL);
	input = up_input(argv);
	if (input != NULL)
	{
		if ((get_tok_str(input, env, exit_code, &tok)) == 1)
			return (NULL);
	}
	return (tok);
}
