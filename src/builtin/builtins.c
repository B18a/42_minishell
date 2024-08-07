/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 23:05:50 by psanger           #+#    #+#             */
/*   Updated: 2024/05/22 20:35:56 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	init_env(t_env **env)
{
	char	buffer_cwd[PATH_MAX];
	char	*temp;

	getcwd(buffer_cwd, PATH_MAX);
	temp = ft_strjoin("PWD=", buffer_cwd);
	ft_export(env, temp);
	free(temp);
	return (0);
}

char	*get_key(char *argv)
{
	int		i;
	char	*key;

	i = 0;
	key = NULL;
	while (argv[i] != '\0' && argv[i] != '=')
		i++;
	key = ft_substr(argv, 0, i);
	return (key);
}

int	fill_env(t_env **env, char *argv)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	new_node->value = ft_strdup(argv);
	new_node->key = get_key(argv);
	new_node->next = NULL;
	env_lstadd_back(env, new_node);
	return (0);
}

t_env	*get_env(char **env_start)
{
	t_env	*env;
	int		i;

	i = 0;
	env = NULL;
	if (env_start == NULL || env_start[0] == NULL)
	{
		init_env(&env);
	}
	else
	{
		while (env_start[i] != NULL)
		{
			fill_env(&env, env_start[i]);
			i++;
		}
	}
	return (env);
}
