/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:45:11 by psanger           #+#    #+#             */
/*   Updated: 2024/05/24 19:58:50 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_echo(char **argv)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (argv[1] == NULL)
		return (printf("\n"), 0);
	if (ft_strncmp(argv[1], "-n", 3) == 0)
	{
		new_line = 0;
		i++;
	}
	while (argv[i] != NULL)
	{
		printf("%s", argv[i]);
		i++;
		if (argv[i] != NULL)
			printf(" ");
	}
	if (new_line == 1)
		printf("\n");
	return (0);
}
