/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tok_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:45:14 by psanger           #+#    #+#             */
/*   Updated: 2024/05/24 18:24:49 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redirect_helper(char **input, t_tok **tok, int *i, int *exit_code)
{
	*i += 1;
	if (input[*i] == NULL)
	{
		free_input(input);
		free_mem(*tok);
		*exit_code = 258;
		printf("minishell: syntax error near unexpected token `newline'\n");
		tok = NULL;
		return (1);
	}
	return (0);
}

int	get_tok_str(char **input, t_env **env, int *exit_code, t_tok **tok)
{
	int	i;
	int	is_redirect;

	i = -1;
	is_redirect = 0;
	while (input[++i] != NULL)
	{
		input[i] = expand_input(input[i], env, *exit_code);
		is_redirect = get_redirect_type(input[i]);
		if (is_redirect != 0)
		{
			if (redirect_helper(input, tok, &i, exit_code) == 1)
				return (1);
			input[i] = expand_input(input[i], env, *exit_code);
			ft_tok_add_back(tok, (ft_tok_new(input[i], is_redirect)));
		}
		else if (ft_strncmp(input[i], "|", 2) == 0)
			ft_tok_add_back(tok, (ft_tok_new(input[i], PIPE)));
		else if (check_for_buildins(input[i]) == 1)
			ft_tok_add_back(tok, (ft_tok_new(input[i], BUILTIN)));
		else if (ft_strncmp(input[i], "", 1) != 0)
			ft_tok_add_back(tok, ft_tok_new(input[i], CMD));
	}
	free_input(input);
	return (0);
}
