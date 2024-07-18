/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_get_new_len.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:37:25 by psanger           #+#    #+#             */
/*   Updated: 2024/05/23 17:00:35 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	is_expantion_len(int *i, int *len, t_env **env, char *argv)
{
	char	*temp1;
	char	*temp2;
	int		j;

	temp1 = NULL;
	temp2 = NULL;
	j = 0;
	while (argv[*i] != '\0' && argv[*i] != ' ' && argv[*i] != '\''
		&& argv[*i] != '\"' && argv[*i] != '\n')
	{
		j++;
		*i += 1;
	}
	temp1 = ft_substr(argv, *i - j + 1, j - 1);
	temp2 = expander(temp1, env);
	*len += ft_strlen(temp2);
	if (temp1 != NULL)
		free(temp1);
	if (temp2 != NULL)
		free(temp2);
}

void	is_exit_code_len(int *i, int *len, int exit_code)
{
	char	*temp;

	*i += 2;
	temp = ft_itoa(exit_code);
	*len += ft_strlen(temp);
	free(temp);
}

int	get_res_len_expander(char *argv, t_env **env, int exit_code)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] == '$' && argv[i + 1] != '\0' && argv[i + 1] != ' '
			&& argv[i + 1] != '\'' && argv[i + 1] != '\"'
			&& argv[i + 1] != '\n')
		{
			if (argv[i + 1] == '?')
				is_exit_code_len(&i, &len, exit_code);
			else
				is_expantion_len(&i, &len, env, argv);
		}
		i++;
		len++;
	}
	return (len);
}
