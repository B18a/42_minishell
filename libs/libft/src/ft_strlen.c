/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:26:17 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/03 20:39:39 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	if (s == NULL)
		return (0);
	while (s[counter] != '\0')
	{
		counter++;
	}
	return (counter);
}
