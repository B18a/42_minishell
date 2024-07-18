/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_cpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:47:46 by psanger           #+#    #+#             */
/*   Updated: 2024/05/23 16:59:57 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cpy_len(int index[2], int *j, char *argv)
{
	while (argv[index[0]] != '\0' && argv[index[0]] != ' '
		&& argv[index[0]] != '\'' && argv[index[0]] != '\"'
		&& argv[index[0]] != '\n')
	{
		*j += 1;
		index[0] += 1;
	}
}

void	cpy_expantion(int index[2], char *argv, t_env **env, char *res)
{
	char	*temp1;
	char	*temp2;
	int		j;
	int		l;

	temp1 = NULL;
	temp2 = NULL;
	j = 0;
	l = 0;
	cpy_len(index, &j, argv);
	temp1 = ft_substr(argv, index[0] - j + 1, j - 1);
	temp2 = expander(temp1, env);
	if (temp1 != NULL)
		free(temp1);
	if (temp2 != NULL)
	{
		while (temp2[l] != '\0')
		{
			res[index[1]] = temp2[l];
			index[1] += 1;
			l++;
		}
		free(temp2);
	}
}

void	is_exit_code_cpy(int index[2], char *res, int exit_code)
{
	char	*temp;
	int		m;

	m = 0;
	temp = NULL;
	index[0] += 2;
	temp = ft_itoa(exit_code);
	while (temp[m] != '\0')
	{
		res[index[1]] = temp[m];
		index[1] += 1;
		m++;
	}
	free(temp);
}

char	*get_res_expander(char *argv, t_env **env, char *res, int exit_code)
{
	int	index[2];

	index[0] = 0;
	index[1] = 0;
	while (argv[index[0]] != '\0')
	{
		if (argv[index[0]] == '$'
			&& argv[index[0] + 1] != '\0' && argv[index[0] + 1] != ' '
			&& argv[index[0] + 1] != '\'' && argv[index[0] + 1] != '\"'
			&& argv[index[0] + 1] != '\n')
		{
			if (argv[index[0] + 1] == '?')
				is_exit_code_cpy(index, res, exit_code);
			else
				cpy_expantion(index, argv, env, res);
		}
		res[index[1]] = argv[index[0]];
		index[0]++;
		index[1]++;
	}
	res[index[1]] = '\0';
	return (res);
}
