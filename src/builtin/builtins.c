/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 23:05:50 by psanger           #+#    #+#             */
/*   Updated: 2024/05/10 10:59:16 by ajehle           ###   ########.fr       */
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
	int		j;
	char	*key;

	i = 0;
	j = 0;
	while (argv[i] != '\0' && argv[i] != '=')
		i++;
	if (argv[i] == '\0')
		return (NULL);
	key = malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		key[j] = argv[j];
		j++;
	}
	key[j] = '\0';
	return (key);
}

int	fill_env(t_env **env, char *argv)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	new_node->value = malloc(sizeof(char) * (ft_strlen(argv) + 1));
	ft_strlcpy(new_node->value, argv, (ft_strlen(argv) + 1));
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
