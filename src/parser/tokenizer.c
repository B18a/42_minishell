/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:42:09 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/10 15:47:42 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*quote_string(t_input *input, int quote)
{
	char	token_char[2];
	char	*token;
	char	*token_temp;
	int		i;
	int		start;

	i = 0;
	token_char[1] = '\0';
	token = NULL;
	token_temp = NULL;
	if (input)
	{
		input->i++;
		start = input->i;
		while (input && input->line[input->i]
			&& !(is_quote(input->line[input->i]) == quote))
		{
			if (input->i < input->len)
				increase_values(&input->i, &i);
		}
		token = ft_substr(input->line, start, i);
		if (!(is_quote(input->line[input->i]) == quote))
			return (free(token), NULL);
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
			return (OUTFILE);
	}
	else
	{
		if (input->line[input->i + 1] && input->line[input->i + 1] == '<')
		{
			input->i += 1;
			return (HEREDOC);
		}
		else
			return (INFILE);
	}
}

char	*normal_string(t_input *input)
{
	char	token_char[2];
	char	*token;
	char	*token_temp;

	token_char[1] = '\0';
	token = NULL;
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
			token = ft_strjoin_free(token_temp, token_char);
			if (!token)
				return (NULL);
			if (input->i < input->len)
				input->i++;
		}
		input->i--;
	}
	return (token);
}

t_input	*init_input(char *argv)
{
	t_input	*input;

	input = malloc(sizeof(t_input) * 1);
	if (!input)
		return (NULL);
	input->i = 0;
	input->len = ft_strlen(argv);
	input->line = argv;
	return (input);
}

t_tok	*tokenizer(char *argv)
{
	char	quote;
	t_tok	*tok;
	t_input	*input;

	input = init_input(argv);
	tok = NULL;
	while (input && argv[input->i] && argv[skip_spaces(argv, input->i)])
	{
		input->i = skip_spaces(argv, input->i);
		if (is_quote(argv[input->i]))
			ft_tok_add_back(&tok, (ft_tok_new(quote_string(input,
							is_quote(argv[input->i])),
						is_quote(argv[input->i]))));
		else if (argv[input->i] == '|')
			ft_tok_add_back(&tok, (ft_tok_new(NULL, PIPE)));
		else if (argv[input->i] == '<' || argv[input->i] == '>')
			ft_tok_add_back(&tok, (ft_tok_new(NULL, redirect_type(input))));
		else if (!is_special_char(argv[input->i]))
			ft_tok_add_back(&tok, (ft_tok_new(normal_string(input), ARG)));
		if (input->i < input->len)
			input->i++;
	}
	if (input)
		free(input);
	return (tok);
}

// t_tok	*tokenizer(char *argv)
// {
// 	// char	quote;
// 	char	*token;
// 	t_tok	*tok;
// 	t_input	*input;

// 	input = malloc(sizeof(t_input) * 1);
// 	input->i = 0;
// 	input->len = ft_strlen(argv);
// 	input->line = argv;
// 	tok = NULL;
// 	while (argv[input->i] && argv[skip_spaces(argv, input->i)])
// 	{
// 		input->i = skip_spaces(argv, input->i);
// 		// quote = is_quote(argv[input->i]);
// 		// if (quote)
// 		if (argv[input->i] == 34 || argv[input->i] == 39)
// 		{
// 			// token = quote_string(input, quote);
// 			token = quote_string(input, argv[input->i]);
// 			// if (!token)
// 			// 	printf("ERROR IN QUOTE STRING\n");
// 			// ft_tok_add_back(&tok, (ft_tok_new(token, quote)));
// 			ft_tok_add_back(&tok, (ft_tok_new(token, argv[input->i])));
// 		}
// 		else if (argv[input->i] == '|')
// 			ft_tok_add_back(&tok, (ft_tok_new(NULL, PIPE)));
// 		else if (argv[input->i] == '<' || argv[input->i] == '>')
// 			ft_tok_add_back(&tok, (ft_tok_new(NULL, redirect_type(input))));
// 		else if (!is_special_char(argv[input->i]))
// 		{
// 			token = normal_string(input);
// 			// if (!token)
// 			// 	printf("ERROR IN NORMAL STRING\n");
// 			ft_tok_add_back(&tok, (ft_tok_new(token, ARG)));
// 		}
// 		if (input->i < input->len)
// 			input->i++;
// 	}
// 	free(input);
// 	return (tok);
// }
