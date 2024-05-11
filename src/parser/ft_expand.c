/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 23:02:09 by psanger           #+#    #+#             */
/*   Updated: 2024/05/10 15:48:36 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_res_len(char *argv, t_env **env)
{
	char	*temp[2];
	int		len;
	int		i;
	int		j;

	init_values(&i, &j);
	len = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] == '$')
		{
			while (is_allowed_char(argv[i]))
				increase_values(&j, &i);
			temp[0] = ft_substr(argv, i - j + 1, j - 1);
			temp[1] = expander(temp[0], env);
			len += ft_strlen(temp[1]);
			if (temp[0] != NULL)
				free(temp[0]);
			if (temp[1] != NULL)
				free(temp[1]);
			j = 0;
		}
		increase_values(&i, &len);
	}
	return (len);
}

void	get_res_helper(char **temp, int *count, char *res)
{
	while ((temp[1])[count[3]] != '\0')
	{
		res[count[2]] = temp[1][count[3]];
		increase_values(&(count[2]), &(count[3]));
	}
	free(temp[1]);
}

char	*get_res(char *argv, t_env **env, char *res)
{
	char	*temp[2];
	int		count[4];

	init_values(&(count[0]), &(count[1]));
	init_values(&(count[2]), &(count[3]));
	while (argv[count[0]] != '\0')
	{
		if (argv[count[0]] == '$')
		{
			while (is_allowed_char(argv[count[0]]))
				increase_values(&(count[0]), &(count[1]));
			temp[0] = ft_substr(argv, count[0] - count[1] + 1, count[1] - 1);
			temp[1] = expander(temp[0], env);
			if (temp[0] != NULL)
				free(temp[0]);
			if (temp[1] != NULL)
				get_res_helper(temp, count, res);
			init_values(&(count[1]), &(count[3]));
		}
		res[count[2]] = argv[count[0]];
		increase_values(&(count[0]), &(count[2]));
	}
	res[count[2]] = '\0';
	return (res);
}

char	*ft_expand(char *argv, t_env **env, int type)
{
	char	*res;
	int		size;

	res = NULL;
	if (type == QUOTE)
		return (argv);
	size = get_res_len(argv, env);
	res = malloc(sizeof(char) * (size + 1));
	res = get_res(argv, env, res);
	free(argv);
	return (res);
}

// wenn nach dem dollar kein key kommt,
// darf das dollar im string nicht gel'scht werden
