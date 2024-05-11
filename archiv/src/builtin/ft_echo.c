/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:45:11 by psanger           #+#    #+#             */
/*   Updated: 2024/04/29 15:42:12 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_echo(char **argv)
{
	int	i;
	int	new_line;

	i = 1;
	while (argv[i] != NULL)
	{
		prinf("%s", argv[i]);
		i++;
	}
	return (0);
}
