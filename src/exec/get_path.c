/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:57:27 by psanger           #+#    #+#             */
/*   Updated: 2024/05/22 18:51:53 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strjoin_free(char *str, char *str2)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(str2) + 1));
	while (str[i] != '\0')
	{
		dest[i] = str[i];
		i++;
	}
	while (str2[j] != '\0')
	{
		dest[i + j] = str2[j];
		j++;
	}
	dest[i + j] = '\0';
	free(str);
	return (dest);
}

void	free_old_path(char **exe_path)
{
	int	i;

	i = 0;
	if (exe_path)
	{
		while (exe_path[i])
		{
			free(exe_path[i]);
			i++;
		}
		free(exe_path);
	}
}

char	**get_exe_path(t_env **env)
{
	char	*env_path;
	char	**exe_path;

	env_path = NULL;
	exe_path = NULL;
	env_path = expander("PATH", env);
	if (!env_path)
		return (NULL);
	exe_path = ft_split(env_path, ':');
	free(env_path);
	return (exe_path);
}

char	*get_path(char *argv, t_env **env)
{
	char	*path;
	char	**exe_path;
	int		i;

	i = 0;
	if (argv == NULL)
		return (NULL);
	exe_path = get_exe_path(env);
	if (!exe_path)
		return (NULL);
	while (exe_path && exe_path[i])
	{
		exe_path[i] = ft_strjoin_free(exe_path[i], "/");
		exe_path[i] = ft_strjoin_free(exe_path[i], argv);
		if (access(exe_path[i], X_OK) == 0)
		{
			path = ft_strdup(exe_path[i]);
			free_old_path(exe_path);
			return (path);
		}
		i++;
	}
	free_old_path(exe_path);
	return (NULL);
}
