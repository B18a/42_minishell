/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:12:15 by psanger           #+#    #+#             */
/*   Updated: 2024/05/22 17:49:54 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expand_in_dquotes(int *i, t_expand_input *in)
{
	int	j;

	j = 0;
	*i += 1;
	j = *i;
	while (in->input[*i] != '\"' && in->input[*i] != '\0')
		*i += 1;
	in->temp = ft_substr(in->input, j, *i - j);
	in->temp = ft_expand(in->temp, &in->env, DQUOTE, in->exit_code);
	*i += 1;
}

void	expand_in_squotes(int *i, t_expand_input *in)
{
	int	j;

	j = 0;
	*i += 1;
	j = *i;
	while (in->input[*i] != '\'' && in->input[*i] != '\0')
		*i += 1;
	in->temp = ft_substr(in->input, j, *i - j);
	in->temp = ft_expand(in->temp, &in->env, QUOTE, in->exit_code);
	*i += 1;
}

void	expand_no_quotes(int *i, t_expand_input *in)
{
	int	j;

	j = *i;
	while (in->input[*i] != '\'' && in->input[*i] != '\"'
		&& in->input[*i] != '\0')
		*i += 1;
	in->temp = ft_substr(in->input, j, *i - j);
	in->temp = ft_expand(in->temp, &in->env, ARG, in->exit_code);
}

char	*expand_input(char *input, t_env **env, int exit_code)
{
	char			*res;
	t_expand_input	in;

	in.env = *env;
	in.exit_code = exit_code;
	in.temp = NULL;
	in.input = input;
	in.i = 0;
	res = strdup("");
	while (in.input[in.i] != '\0')
	{
		if (in.input[in.i] == '\'')
			expand_in_squotes(&in.i, &in);
		else if (in.input[in.i] == '\"')
			expand_in_dquotes(&in.i, &in);
		else
			expand_no_quotes(&in.i, &in);
		if (in.temp != NULL)
		{
			res = ft_strjoin_free(res, in.temp);
			free(in.temp);
		}
	}
	free(in.input);
	return (res);
}
