/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_two_d_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 21:11:12 by psanger           #+#    #+#             */
/*   Updated: 2024/05/18 11:56:47 by ajehle           ###   ########.fr       */
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

char	**cpy_two_d_arr(int len, char **str1, char **str2)
{
	char	**res;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	res = (char **)malloc(sizeof(char *) * (len + 1));
	if (str1 == NULL || str2 == NULL || res == NULL)
		return (NULL);
	while (str1[i] != NULL)
	{
		if (ft_strncmp(str1[i], "", 1) != 0)
		{
			res[k] = ft_strdup(str1[i]);
			k++;
		}
		i++;
	}
	while (str2[j] != NULL)
	{
		if (ft_strncmp(str2[j], "", 1) != 0)
		{
			res[k] = ft_strdup(str2[j]);
			k++;
		}
		j++;
	}
	res[k] = NULL;
	return (res);
}

char	**join_two_d_arr(char **str1, char **str2)
{
	char	**res;
	int		len;

	res = NULL;
	len = 0;
	len = get_two_d_arr_len(str1, str2);
	res = cpy_two_d_arr(len, str1, str2);
	print_2d_arr(res);
	free_args(str1);
	return (res);
}


