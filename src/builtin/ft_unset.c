/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 01:38:04 by psanger           #+#    #+#             */
/*   Updated: 2024/04/26 02:43:02 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset(t_env **env, char *argv)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env;
	prev = NULL;
	while (curr != NULL)
	{
		if (ft_strncmp(argv, curr->key, ft_strlen(argv) + 1) == 0)
		{
			if (prev == NULL)
				*env = curr->next;
			else
				prev->next = curr->next;
			free(curr->value);
			free(curr->key);
			free(curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}
