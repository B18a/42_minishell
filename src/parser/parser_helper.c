/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:10:46 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/23 21:41:09 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_redirect(int type)
{
	if (type == INFILE || type == OUTFILE || type == APPEND || type == HEREDOC)
		return (1);
	return (0);
}

int	is_option(char *c)
{
	if (c && c[0] == '-')
		return (1);
	else
		return (0);
}

int	is_cmd(char *arg)
{
	if (!ft_strncmp(arg, "ls\0", 3))
	{
		return (1);
	}
	else if (!ft_strncmp(arg, "grep\0", 5))
	{
		return (1);
	}
	else
		return (0);
}

char	*ft_join_with_space(char const *s1, char const *s2)
{
	char	*join;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (len1 + len2 + 2));
	if (!join)
		return (NULL);
	if (len1)
	{
		ft_strlcpy(join, s1, len1 + 1);
		join[len1] = ' ';
	}
	if (len2)
		ft_strlcpy(&join[len1 + 1], s2, len2 + 1);
	return (join);
}

int	get_pipes(t_tok *tok)
{
	int	pipes;

	pipes = 0;
	while (tok)
	{
		if (tok->type == PIPE)
			pipes++;
		tok = tok->next;
	}
	return (pipes);
}
