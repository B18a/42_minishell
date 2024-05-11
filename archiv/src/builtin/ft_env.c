/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 00:05:02 by psanger           #+#    #+#             */
/*   Updated: 2024/04/26 01:17:24 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_shell_lvl(t_env **env)
{
	int		shell_lvl_i;
	char	*shell_lvl_str;
	char	*shlvl;
	char	*temp;

	shell_lvl_i = 0;
	shell_lvl_str = NULL;
	shlvl = NULL;
	temp = NULL;
	shell_lvl_str = expander("SHLVL", env);
	if (shell_lvl_str != NULL)
	{
		shell_lvl_i = ft_atoi(shell_lvl_str);
		free(shell_lvl_str);
	}
	else
		shell_lvl_i = 0;
	shell_lvl_i++;
	shlvl = ft_itoa(shell_lvl_i);
	temp = ft_strjoin("SHLVL=", shlvl);
	ft_export(env, temp);
	free(temp);
	free(shlvl);
	return (0);
}

int	ft_env(t_env **env)
{
	t_env *curr;

	curr = *env;
	while (curr != NULL)
	{
		printf("%s\n", curr->value);
		curr = curr->next;
	}
	return (0);
}
