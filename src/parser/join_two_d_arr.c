/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_two_d_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 21:11:12 by psanger           #+#    #+#             */
/*   Updated: 2024/05/23 22:49:08 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_two_d_arr_len(char **str1, char **str2)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	if (str1 == NULL || str2 == NULL)
		return (0);
	while (str1[i] != NULL)
	{
		if (ft_strncmp(str1[i], "", 1) != 0)
			k++;
		i++;
	}
	while (str2[j] != NULL)
	{
		if (ft_strncmp(str2[j], "", 1) != 0)
			k++;
		j++;
	}
	return (k);
}

void	init_counters(int *count, int a, int b, int c)
{
	count[0] = a;
	count[1] = b;
	count[2] = c;
}

char	**cpy_two_d_arr(int len, char **str1, char **str2)
{
	char	**res;
	int		count[3];

	init_counters(count, 0, 0, 0);
	res = (char **)malloc(sizeof(char *) * (len + 1));
	if (str1 == NULL || str2 == NULL || res == NULL)
		return (NULL);
	while (str1[count[0]] != NULL)
	{
		if (ft_strncmp(str1[count[0]], "", 1) != 0)
			res[count[2]++] = ft_strdup(str1[count[0]]);
		count[0]++;
	}
	while (str2[count[1]] != NULL)
	{
		if (ft_strncmp(str2[count[1]], "", 1) != 0)
			res[count[2]++] = ft_strdup(str2[count[1]]);
		count[1]++;
	}
	res[count[2]] = NULL;
	return (res);
}

char	**join_two_d_arr(char **str1, char **str2)
{
	char	**res;
	int		len;

	res = NULL;
	len = get_two_d_arr_len(str1, str2);
	res = cpy_two_d_arr(len, str1, str2);
	free_args(str1);
	return (res);
}
