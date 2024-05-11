/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 00:22:59 by psanger           #+#    #+#             */
/*   Updated: 2024/05/03 13:50:29 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_key(char *key)
{
	int	i;

	i = 0;
	if (isalpha(key[i]) != 1 && key[0] != '_')
	{
		return (0);
	}
	while (key[i] != '\0')
	{
		if (isalnum(key[i]) != 1 || key[i] == '_')
			return (0);
		i++;
	}
	return (1);
}

t_env	*export_get_new_node(char *key, char *argv)
{
	t_env *new_node = malloc(sizeof(t_env));
	new_node->key = key;
	new_node->value = malloc(sizeof(char) * (ft_strlen(argv) + 1));
	ft_strlcpy(new_node->value, argv, ft_strlen(argv) + 1);
	new_node->next = NULL;
	return (new_node);
}
int	check_old_keys(char *key, char *argv, t_env *curr)
{
	// t_env	*prev;

	// prev = NULL;
	while (curr != NULL)
	{
		if (ft_strncmp(key, curr->key, ft_strlen(key) + 1) == 0)
		{
			free(curr->value);
			curr->value = NULL;
			free(key);
			curr->value = malloc(sizeof(char) * (ft_strlen(argv) + 1));
			ft_strlcpy(curr->value, argv, ft_strlen(argv) + 1);
			return (1);
		}
		// prev = curr;
		curr = curr->next;
	}
	return (0);
}


int	ft_export(t_env **env, char *argv)
{
	char	*key;
	t_env	*curr;
	t_env	*new_node;

	if (argv == NULL) {
		ft_export_no_args(env);
		return (0);
	}
	key = get_key(argv);
	if (key == NULL) {
		return (0);
	}
	curr = *env;
	if (check_old_keys(key, argv, curr) > 0)
	{
		return (0);
	}
	else if (check_key(key) == 1 && argv[ft_strlen(key)] == '=')
	{
		new_node = export_get_new_node(key, argv);
		env_lstadd_back(env, new_node);
		return (0);
	}
	return (0);
}
