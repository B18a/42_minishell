/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:42:09 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/02 16:29:11 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*quote_string(t_input *input, int quote)
{
	char	token_char[2];
	char	*token;
	char	*token_temp;

	token_char[1] = '\0';
	token = NULL;
	token_temp = NULL;
	if (input)
	{
		input->i++;
		token = ft_strdup("");
		if (!token)
			return (NULL);
		while (input && input->line[input->i]
			&& !(is_unique_quote(input->line[input->i]) == quote))
		{
			token_char[0] = input->line[input->i];
			token_temp = token;
			token = ft_strjoin(token_temp, token_char);
			free(token_temp);
			if (!token)
				return (NULL);
			if (input->i < input->len)
				input->i++;
		}
		if (!(is_unique_quote(input->line[input->i]) == quote))
		{
			free(token);
			return (NULL);
		}
	}
	return (token);
}

int	redirect_type(t_input *input)
{
	if (input->line[input->i] == '>')
	{
		if (input->line[input->i + 1] && input->line[input->i + 1] == '>')
		{
			input->i += 1;
			return (APPEND);
		}
		else
		{
			return (OUTFILE);
		}
	}
	else if (input->line[input->i] == '<')
	{
		if (input->line[input->i + 1] && input->line[input->i + 1] == '<')
		{
			input->i += 1;
			return (HEREDOC);
		}
		else
		{
			return (INFILE);
		}
	}
	else
		return (-1); //?????
}

char	*normal_string(t_input *input)
{
	char	token_char[2];
	char	*token;
	char	*token_temp;

	token_char[1] = '\0';
	token = NULL;
	token_temp = NULL;
	if (input)
	{
		token = ft_strdup("");
		if (!token)
			return (NULL);
		while (input && input->line[input->i]
			&& !(is_special_char(input->line[input->i])))
		{
			token_char[0] = input->line[input->i];
			token_temp = token;
			token = ft_strjoin(token_temp, token_char);
			free(token_temp);
			if (!token)
				return (NULL);
			if (input->i < input->len)
				input->i++;
		}
		input->i--;
	}
	return (token);
}

t_tok	*tokenizer(char *argv)
{
	char	*token;
	char	quote;
	t_tok	*tok;
	t_input	*input;

	input = malloc(sizeof(t_input) * 1);
	input->i = 0;
	input->len = ft_strlen(argv);
	input->line = argv;
	token = NULL;
	tok = NULL;
	while (argv[input->i] && argv[skip_spaces(argv, input->i)])
	{
		input->i = skip_spaces(argv, input->i);
		quote = is_unique_quote(argv[input->i]);
		if (quote)
		{
			token = quote_string(input, quote);
			if (!token)
			{
				printf("ERROR IN QUOTE STRING\n");
			}
			ft_tok_add_back(&tok, (ft_tok_new(token, quote)));
		}
		else if (argv[input->i] == '|')
		{
			ft_tok_add_back(&tok, (ft_tok_new(NULL, PIPE)));
		}
		else if (argv[input->i] == '<' || argv[input->i] == '>')
		{
			ft_tok_add_back(&tok, (ft_tok_new(NULL, redirect_type(input))));
		}
		else if (!is_special_char(argv[input->i]))
		{
			token = normal_string(input);
			if (!token)
			{
				// Error in normalstring!
			}
			ft_tok_add_back(&tok, (ft_tok_new(token, ARG)));
		}
		if (input->i < input->len)
			input->i++;
	}
	free(input);
	return (tok);
}
