/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_psanger_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:52:12 by psanger           #+#    #+#             */
/*   Updated: 2024/05/22 16:52:49 by psanger          ###   ########.fr       */
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
