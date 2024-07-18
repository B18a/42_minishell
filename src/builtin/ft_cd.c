/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:24:57 by psanger           #+#    #+#             */
/*   Updated: 2024/05/24 18:24:17 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*handle_dir(char *str)
{
	char	*new;
	char	*temp;
	char	*home;
	int		i;
	int		j;

	i = 0;
	j = 0;
	home = getenv("HOME");
	temp = ft_strjoin(home, str);
	new = malloc(sizeof(char) * (ft_strlen(temp) - 1));
	while (temp[i])
	{
		if (temp[i] != '~')
		{
			new[j] = temp[i];
			j++;
		}
		i++;
	}
	free(temp);
	temp = NULL;
	return (new);
}

int	ft_chdir(t_env **env, char *dir)
{
	char	buffer_cwd[PATH_MAX];
	char	*temp;

	getcwd(buffer_cwd, PATH_MAX);
	temp = ft_strjoin("OLDPWD=", buffer_cwd);
	ft_export(env, temp);
	free(temp);
	temp = dir;
	if (dir && dir[0] == '~')
		dir = handle_dir(temp);
	if (chdir(dir) < 0)
	{
		ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
		return (1);
	}
	getcwd(buffer_cwd, PATH_MAX);
	temp = ft_strjoin("PWD=", buffer_cwd);
	ft_export(env, temp);
	if (temp != NULL)
		free(temp);
	return (0);
}

int	ft_cd(t_env **env, char *dir)
{
	if (dir == NULL)
	{
		dir = expander("HOME", env);
		if (dir == NULL)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	else if (dir[0] == '-' && dir[1] == '\0')
	{
		dir = expander("OLDPWD", env);
		if (dir != NULL)
			printf("%s\n", dir);
		else
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		if (dir == NULL)
			return (0);
	}
	else if (((dir[0] == '~') && (dir[1] == '\0' || (dir[1] == '/'
					&& dir[2] == '\0'))))
		dir = getenv("HOME");
	if (ft_chdir(env, dir) == 1)
		return (1);
	return (0);
}
