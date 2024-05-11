/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:24:57 by psanger           #+#    #+#             */
/*   Updated: 2024/05/10 10:59:32 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cd(t_env **env, char *dir)
{
	char	buffer_cwd[PATH_MAX];
	char	*temp;

	if (dir == NULL)
	{
		dir = getenv("HOME");
		if (dir == NULL)
			return (-1);
	}
	else if (dir[0] == '-' && dir[1] == '\0')
	{
		dir = expander("OLDPWD", env);
		if (dir == NULL)
			return (0);
	}
	else if ((dir[0] == '~' && dir[1] == '\0'))
		dir = getenv("HOME");
	getcwd(buffer_cwd, PATH_MAX);
	temp = ft_strjoin("OLDPWD=", buffer_cwd);
	ft_export(env, temp);
	if (chdir(dir) < 0)
		return (1);
	getcwd(buffer_cwd, PATH_MAX);
	temp = ft_strjoin("PWD=", buffer_cwd);
	ft_export(env, temp);
	if (temp != NULL)
		free(temp);
	return (0);
}
