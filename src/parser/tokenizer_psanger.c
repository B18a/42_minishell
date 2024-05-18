/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_psanger.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:42:35 by psanger           #+#    #+#             */
/*   Updated: 2024/05/18 11:59:44 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_special(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	else
		return (0);
}

int	input_len(char *argv)
{
	int		len;
	int		i;
	int		in_quotes;
	char	temp;

	len = 0;
	i = 0;
	in_quotes = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] == ' ') {
			len++;
			while (argv[i] == ' ')
				i++;
		}
		else if (argv[i] == '\'' || argv[i] == '\"') {
			i++;
			len++;
			while (argv[i] != '\'' && argv[i] != '\"') {
				i++;
				len++;
			}
			i++;
			len++;
		}
		else if (is_special(argv[i]) == 1 && argv[i + 1] != ' ') {
			if (i > 0) {
				if (argv[i - 1] != ' ')
					len++;
			}
			temp = argv[i];
			i++;
			if (argv[i] == temp && temp != '|') {
				len++;
				i++;
			}
			len += 2;
		}
		else {
			i++;
			len++;
		}
		if (argv[i] == '\0')
			return (len);
	}
	return (len);
}

char	*cpy_input(char *argv, int size)
{
	int		j;
	int		i;
	char	quote;
	char	*input;
	char	temp;

	input = malloc(sizeof(char) * (size + 1));
	j = 0;
	i = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] == ' ') {
			input[j] = argv[i];
			j++;
			while (argv[i] == ' ')
				i++;
		}
		if (is_special(argv[i]) == 1) {
			if (i > 0) {
				if (argv[i - 1] != ' ')
				{
					input[j] = ' ';
					j++;
				}
			}
			temp = argv[i];
			input[j] = argv[i];
			j++;
			i++;
			if (argv[i] == temp && temp != '|') {
				input[j] = argv[i];
				j++;
				i++;
			}
			if (argv[i] != '\0' && argv[i] != ' ')
			{
				input[j] = ' ';
				j++;
			}
		}
		if (argv[i] == '\'' || argv[i] == '\"') {
			quote = argv[i];
			input[j] = argv[i];
			i++;
			j++;
			while (argv[i] != quote) {
				input[j] = argv[i];
				i++;
				j++;
			}
			input[j] = argv[i];
			i++;
			j++;
		}
		else
		{
			input[j] = argv[i];
			i++;
			j++;
		}
		if (argv[i] == '\0') {
			input[j] = '\0';
			return (input);
		}
	}
	input[j] = '\0';
	return (input);
}

char	**up_input(char *argv)
{
	char	*input;
	char	*res;
	char	**split;

	input = ft_strtrim(argv, " ");
	free(argv);
	int	size = input_len(input);
	res = cpy_input(input, size);
	free(input);
	split = split_with_quotes(res, ' ');
	free(res);
	return (split);
}

char	*expand_input(char *input, t_env **env, int exit_code)
{
	int		i;
	int		j;
	int		k;
	char	*temp;
	char	*res;

	i = 0;
	j = 0;
	k = 0;
	res = strdup("");
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
		{
			i++;
			j = i;
			while (input[i] != '\'' && input[i] != '\0')
				i++;
			temp = ft_substr(input, j, i - j);
			temp = ft_expand(temp, env, QUOTE, exit_code);
			k++;
			i++;
		}
		else if (input[i] == '\"')
		{
			i++;
			j = i;
			while (input[i] != '\"' && input[i] != '\0')
				i++;
			temp = ft_substr(input, j, i - j);
			temp = ft_expand(temp, env, DQUOTE, exit_code);
			k++;
			i++;
		}
		else
		{
			j = i;
			while (input[i] != '\'' && input[i] != '\"' && input[i] != '\0')
				i++;
			temp = ft_substr(input, j, i - j);
			temp = ft_expand(temp, env, ARG, exit_code);
			k++;
		}
		if (temp != NULL)
		{
			res = ft_strjoin_free(res, temp);
			free(temp);
		}
	}
	free(input);
	return (res);
}

int	get_redirect_type(char *input)
{
	if (ft_strncmp(input, ">", 2) == 0)
		return (OUTFILE);
	if (ft_strncmp(input, ">>", 3) == 0)
		return (APPEND);
	if (ft_strncmp(input, "<", 2) == 0)
		return (INFILE);
	if (ft_strncmp(input, "<<", 3) == 0)
		return (HEREDOC);
	return (0);
}

t_tok_ps	*ft_tok_new_psanger(char *content, int type)
{
	t_tok_ps	*new;
	new = (t_tok_ps *)malloc(sizeof(t_tok_ps));
	if (!new)
		return (NULL);
	new->content = (char **)malloc(sizeof(char *) * 1);
	new->content[0] = (char *)malloc(sizeof(char) * (ft_strlen(content) + 1));
	ft_strlcpy(new->content[0], content, ft_strlen(content) + 1);
	new->content[1] = NULL;
	new->type = type;
	new->syntax_error = FALSE;
	new->next = NULL;
	return (new);
}


void	get_tok_str(char **input, t_env **env, int exit_code, t_tok **tok)
{
	int		i;
	int		is_redirect;

	i = 0;
	is_redirect = 0;
	while (input[i] != NULL)
	{
		input[i] = expand_input(input[i], env, exit_code);
		is_redirect = get_redirect_type(input[i]);
		if (is_redirect != 0) {
			i++;
			input[i] = expand_input(input[i], env, exit_code);
			ft_tok_add_back(tok, (ft_tok_new(input[i], is_redirect)));
		}
		else if (ft_strncmp(input[i], "|", 2) == 0)
			ft_tok_add_back(tok, (ft_tok_new(input[i], PIPE)));
		else if (check_for_buildins(input[i]) == 1)
			ft_tok_add_back(tok, (ft_tok_new(input[i], BUILTIN)));
		else {
			if(ft_strncmp(input[i], "", 1) != 0)
				ft_tok_add_back(tok, ft_tok_new(input[i], CMD));
		}
		i++;
	}
	free_args(input);
	// i = 0;
	// while(input[i] != NULL)
	// {
	// 	free(input[i]);
	// 	i++;
	// }
	// free(input);
}




t_tok	*tokenizer_psanger(char *argv, t_env **env, int exit_code)
{
	char	**input = NULL;
	t_tok	*tok = NULL;

	input = up_input(argv);
	// for (size_t i = 0; input[i] != NULL ; i++)
	// 	printf("%s%s\n%s", BLUE ,input[i], RESET);
	get_tok_str(input, env, exit_code, &tok);
	return (tok);
}
