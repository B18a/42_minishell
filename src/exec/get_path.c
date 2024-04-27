/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:57:27 by psanger           #+#    #+#             */
/*   Updated: 2024/04/25 16:58:35 by psanger          ###   ########.fr       */
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



char	*get_path(char *argv)
{
	char *env = getenv("PATH");
	char **exe_path = ft_split(env, ':');
	int i = 0;
	while (exe_path[i]) {
		exe_path[i] = ft_strjoin_free(exe_path[i], "/");
		exe_path[i] = ft_strjoin_free(exe_path[i], argv);
		if (access(exe_path[i], X_OK) == 0)
		{
			// printf("%s\n", exe_path[i]);
			return (exe_path[i]);
		}
		i++;
	}
	printf("command not found\n");
	return (NULL);
}
