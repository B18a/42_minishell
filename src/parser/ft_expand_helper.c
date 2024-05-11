/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 23:02:09 by psanger           #+#    #+#             */
/*   Updated: 2024/05/10 15:47:54 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	increase_values(int *a, int *b)
{
	if (a)
		(*a)++;
	if (b)
		(*b)++;
}

void	init_values(int *a, int *b)
{
	if (a)
		(*a) = 0;
	if (b)
		(*b) = 0;
}

int	is_allowed_char(char c)
{
	if (c != '\0' && c != ' ' && c != '\'' && c != '\"' && c != '\n')
	{
		return (1);
	}
	return (0);
}
