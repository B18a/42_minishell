/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:24:57 by psanger           #+#    #+#             */
/*   Updated: 2024/05/15 21:03:11 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cd(t_env **env, char *dir)
{
	char	buffer_cwd[PATH_MAX];
	char	*temp;

	if (dir == NULL) {
		dir = expander("HOME", env);
		if (dir == NULL) {
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}

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
	if (chdir(dir) < 0) {
		ft_putstr_fd(" No such file or directory\n", 2);
		return (1);
	}
	getcwd(buffer_cwd, PATH_MAX);
	temp = ft_strjoin("PWD=", buffer_cwd);
	ft_export(env, temp);
	if (temp != NULL)
		free(temp);
	return (0);
}
