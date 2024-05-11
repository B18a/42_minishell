/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_no_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 01:19:47 by psanger           #+#    #+#             */
/*   Updated: 2024/05/10 11:05:08 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*get_env_copy(t_env **env)
{
	t_env	*curr;
	t_env	*env_cpy;
	t_env	*prev;
	t_env	*new_node;

	curr = *env;
	env_cpy = NULL;
	prev = NULL;
	while (curr != NULL)
	{
		new_node = malloc(sizeof(t_env));
		new_node->key = NULL;
		new_node->value = malloc(ft_strlen(curr->value) + 1);
		ft_strlcpy(new_node->value, curr->value, ft_strlen(curr->value) + 1);
		if (env_cpy == NULL)
			env_cpy = new_node;
		else
			prev->next = new_node;
		prev = new_node;
		curr = curr->next;
	}
	return (env_cpy);
}

int	sort_env_cpy(t_env *env_cpy)
{
	t_env	*curr;
	char	*temp;

	if (env_cpy == NULL || env_cpy->next == NULL)
		return (1);
	curr = env_cpy;
	while (curr->next != NULL)
	{
		if (ft_strncmp(curr->value, curr->next->value, ft_strlen(curr->value) + 1) > 0)
		{
			temp = curr->value;
			curr->value = curr->next->value;
			curr->next->value = temp;
			curr = env_cpy;
		}
		else
			curr = curr->next;
	}
	return (0);
}

int	ft_export_no_args(t_env **env)
{
	t_env	*env_cpy;
	t_env	*prev;

	env_cpy = get_env_copy(env);
	sort_env_cpy(env_cpy);
	prev = NULL;
	while (env_cpy != NULL)
	{
		if (prev != NULL)
		{
			free(prev->value);
			free(prev);
		}
		printf("declare -x \"%s\"\n", env_cpy->value);
		prev = env_cpy;
		env_cpy = env_cpy->next;
	}
	free(prev->value);
	free(prev);
	return (0);
}
