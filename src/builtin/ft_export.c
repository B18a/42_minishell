/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 00:22:59 by psanger           #+#    #+#             */
/*   Updated: 2024/05/24 17:29:16 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_key(char *key)
{
	int	i;

	i = 0;
	if (ft_isalpha(key[i]) != 1 && key[0] != '_')
		return (1);
	while (key[i] != '\0')
	{
		if (ft_isalnum(key[i]) != 1 || key[i] == '_')
			return (1);
		i++;
	}
	return (0);
}

t_env	*export_get_new_node(char *key, char *argv)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(argv);
	new_node->next = NULL;
	return (new_node);
}

int	check_old_keys(char *key, char *argv, t_env *curr)
{
	while (curr != NULL)
	{
		if (ft_strncmp(key, curr->key, ft_strlen(key) + 1) == 0)
		{
			free(curr->value);
			curr->value = NULL;
			free(key);
			key = NULL;
			curr->value = ft_strdup(argv);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

int	ft_export(t_env **env, char *argv)
{
	char	*key;
	t_env	*curr;
	t_env	*new_node;

	if (argv == NULL)
		return (ft_export_no_args(env), 0);
	key = get_key(argv);
	if (check_key(key) == 1)
	{
		putstr_fd("minishell: export: `", key, "': not a valid identifier\n",
			2);
		free(key);
		return (1);
	}
	curr = *env;
	if (check_old_keys(key, argv, curr) > 0)
		return (0);
	else if (check_key(key) == 0 && argv[ft_strlen(key)] == '=')
	{
		new_node = export_get_new_node(key, argv);
		env_lstadd_back(env, new_node);
	}
	free(key);
	return (0);
}
