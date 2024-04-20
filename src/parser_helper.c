/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:10:46 by ajehle            #+#    #+#             */
/*   Updated: 2024/04/20 13:55:15 by ajehle           ###   ########.fr       */
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

char	*ft_str_cmd_join(char const *s1, char const *s2)
{
	char	*join;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * len + 2);
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, ft_strlen(s1) + 1);
	join[ft_strlen(s1)] = ' ';
	ft_strlcpy(&join[ft_strlen(s1) + 1], s2, ft_strlen(s2) + 1);
	printf("JOINED STRING %s\n", join);
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
