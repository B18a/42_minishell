/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 23:02:09 by psanger           #+#    #+#             */
/*   Updated: 2024/05/15 21:17:25 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	get_res_len(char *argv, t_env **env, int exit_code)
// {
// 	char *temp1;
// 	char *temp2;
// 	int	len;
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	len = 0;
// 	while (argv[i] != '\0')
// 	{
// 		if (argv[i] == '$' && argv[i + 1] != '\0' && argv[i + 1] != ' ' && argv[i + 1] != '\'' && argv[i + 1] != '\"' && argv[i + 1] != '\n')
// 		{
// 			if (argv[i + 1] == '?')
// 			{
// 				i += 2;
// 				len += ft_strlen(ft_itoa(exit_code));
// 			}
// 			else
// 			{
// 				while (argv[i] != '\0' && argv[i] != ' ' && argv[i] != '\'' && argv[i] != '\"' && argv[i] != '\n') {
// 					j++;
// 					i++;
// 				}
// 				temp1 = ft_substr(argv, i - j + 1, j - 1);
// 				temp2 = expander(temp1, env);
// 				len += ft_strlen(temp2);
// 				if (temp1 != NULL)
// 					free(temp1);
// 				if (temp2 != NULL)
// 					free(temp2);
// 				j = 0;
// 			}
// 		}
// 		i++;
// 		len++;
// 	}
// 	return (len);
// }

// void	cpy_exit_code(int exit_code, char *res, int *index, int *k)
// {
// 	char	*temp;
// 	int		m;
// 	int		i;

// 	i = *k;
// 	m = 0;
// 	temp = NULL;
// 	*index += 2;
// 	temp = ft_itoa(exit_code);
// 	while (temp[m] != '\0')
// 	{
// 		res[i] = temp[m];
// 		k++;
// 		i++;
// 	}
// 	*k = i;
// }

// void	cpy_expander(int *k, int *i, char *argv, t_env **env, char *res)
// {
// 	char	*temp[2];
// 	int		index[4];

	// index[0] = 0;
	// index[1] = 0;
	// index[2] = *i;
	// index[3] = *k;
// 	while (argv[index[2]] != '\0' && argv[index[2]] != ' '
// 			&& argv[index[2]] != '\'' && argv[index[2]] != '\"' && argv[index[2]] != '\n') {
// 		index[1]++;
// 		index[2]++;
// 	}
// 	temp[0] = ft_substr(argv, index[2] - index[1] + 1, index[1] - 1);
// 	temp[1] = expander(temp[0], env);
// 	if (temp[0] != NULL)
// 		free(temp[0]);
// 	if (temp[1] != NULL)
// 	{
// 		while (temp[1][index[0]++] != '\0')
// 			res[index[3]++] = temp[1][index[0]];
// 		free(temp[1]);
// 	}
// 	*i = index[2];
// 	*k = index[3];
// }


// char	*get_res(char *argv, t_env **env, char *res, int exit_code)
// {
// 	int k;
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	while (argv[i] != '\0')
// 	{
// 		if (argv[i] == '$' && argv[i + 1] != '\0' && argv[i + 1] != ' ' && argv[i + 1] != '\'' && argv[i + 1] != '\"' && argv[i + 1] != '\n')
// 		{
// 			if (argv[i + 1] == '?')
// 				cpy_exit_code(exit_code, res, &i, &k);
// 			else
// 				cpy_expander(&k, &i, argv, env, res);
// 		}
// 		res[k] = argv[i];
// 		i++;
// 		k++;
// 	}
// 	res[k] = '\0';
// 	return (res);
// }

// char	*ft_expand(char *argv, t_env **env, int type, int exit_code)
// {
// 	char *res;
// 	int	size;

// 	size = 0;
// 	res = NULL;
// 	if (type == QUOTE)
// 		return (argv);
// 	size = get_res_len(argv, env, exit_code);
// 	res = malloc(sizeof(char) * (size + 1));
// 	res = get_res(argv, env, res, exit_code);
// 	free(argv);
// 	return (res);
// }

int	get_res_len(char *argv, t_env **env, int exit_code)
{
	char *temp1;
	char *temp2;
	int	len;
	int i;
	int j;

	i = 0;
	j = 0;
	len = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] == '$' && argv[i + 1] != '\0' && argv[i + 1] != ' ' && argv[i + 1] != '\'' && argv[i + 1] != '\"' && argv[i + 1] != '\n')
		{
			if (argv[i + 1] == '?')
			{
				i += 2;
				len += ft_strlen(ft_itoa(exit_code));
			}
			else
			{
				while (argv[i] != '\0' && argv[i] != ' ' && argv[i] != '\'' && argv[i] != '\"' && argv[i] != '\n') {
					j++;
					i++;
				}
				temp1 = ft_substr(argv, i - j + 1, j - 1);
				temp2 = expander(temp1, env);
				len += ft_strlen(temp2);
				if (temp1 != NULL)
					free(temp1);
				if (temp2 != NULL)
					free(temp2);
				j = 0;
			}
		}
		i++;
		len++;
	}
	return (len);
}

char	*get_res(char *argv, t_env **env, char *res, int exit_code)
{
	char *temp1;
	char *temp2;
	char *temp3;
	int k;
	int	len;
	int i;
	int j;
	int	l;
	int m;

	m = 0;
	i = 0;
	j = 0;
	len = 0;
	k = 0;
	l = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] == '$' && argv[i + 1] != '\0' && argv[i + 1] != ' ' && argv[i + 1] != '\'' && argv[i + 1] != '\"' && argv[i + 1] != '\n')
		{
			if (argv[i + 1] == '?')
			{
				i += 2;
				temp3 = ft_itoa(exit_code);
				while (temp3[m] != '\0')
				{
					res[k] = temp3[m];
					k++;
					m++;
				}
			}
			else
			{
				while (argv[i] != '\0' && argv[i] != ' ' && argv[i] != '\'' && argv[i] != '\"' && argv[i] != '\n') {
					j++;
					i++;
				}
				temp1 = ft_substr(argv, i - j + 1, j - 1);
				temp2 = expander(temp1, env);
				len += ft_strlen(temp2);
				if (temp1 != NULL)
					free(temp1);
				if (temp2 != NULL)
				{
					while (temp2[l] != '\0') {
						res[k] = temp2[l];
						k++;
						l++;
					}
					free(temp2);
				}
				j = 0;
				l = 0;
			}
		}
		res[k] = argv[i];
		i++;
		k++;
	}
	res[k] = '\0';
	return (res);
}

char	*ft_expand(char *argv, t_env **env, int type, int exit_code)
{
	char	*res;
	int		size;

	res = NULL;
	if (type == QUOTE)
		return (argv);
	size = get_res_len(argv, env, exit_code);
	res = malloc(sizeof(char) * (size + 1));
	res = get_res(argv, env, res, exit_code);
	free(argv);
	return (res);
}

// wenn nach dem dollar kein key kommt,
// darf das dollar im string nicht gel'scht werden
