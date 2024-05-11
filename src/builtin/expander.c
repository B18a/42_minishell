/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 01:09:54 by psanger           #+#    #+#             */
/*   Updated: 2024/05/03 20:38:56 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*extract(char *str)
{
	int		i;
	int		j;
	char	*val;

	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (NULL);
	i++;
	val = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (val == NULL)
		return (NULL);
	while (str[i + j] != '\0')
	{
		val[j] = str[i + j];
		j++;
	}
	val[j] = '\0';
	return (val);
}

char	*expander(char *key, t_env **env)
{
	t_env	*curr;

	if (env == NULL || key == NULL)
		return (NULL);
	curr = *env;
	while (curr != NULL)
	{
		if (ft_strncmp(key, curr->key, ft_strlen(curr->key) + 1) == 0)
			return (extract(curr->value));
		curr = curr->next;
	}
	return (NULL);
}
