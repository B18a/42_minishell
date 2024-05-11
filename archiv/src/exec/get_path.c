/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:57:27 by psanger           #+#    #+#             */
/*   Updated: 2024/05/03 13:37:05 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strjoin_free(char *str, char *str2)
{
	int	i = 0;
	int	j = 0;
	char	*dest;
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
	if(exe_path)
	{
		while(exe_path[i])
		{
			free(exe_path[i]);
			i++;
		}
		free(exe_path);
	}
}


char	*get_path(char *argv)
{
	char	*path;
	char	*env;
	char	**exe_path;
	int	i;

	i = 0;
	env = getenv("PATH");
	if(!env)
		return (NULL);
	exe_path = ft_split(env, ':');
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
	printf("command not found\n");
	return (NULL);
}
