/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:10:19 by psanger           #+#    #+#             */
/*   Updated: 2024/05/17 14:02:52 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env_arr(char **env_arr)
{
	int	i;

	if (env_arr == NULL)
		return ;
	i = 0;
	while (env_arr[i] != NULL)
	{
		free(env_arr[i]);
		i++;
	}
	free(env_arr);
}

char	**get_env_arr(t_env **env)
{
	char	**env_arr;
	t_env	*curr;
	int		i;

	i = 0;
	curr = *env;
	while (curr != NULL)
	{
		i++;
		curr = curr->next;
	}
	env_arr = malloc(sizeof(char *) * (i + 1));
	curr = *env;
	i = 0;
	while (curr != NULL)
	{
		env_arr[i] = malloc(sizeof(char) * (ft_strlen(curr->value) + 1));
		ft_strlcpy(env_arr[i], curr->value, ft_strlen(curr->value) + 1);
		i++;
		curr = curr->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

int	check_dot(t_msh *list, t_env **env)
{
	struct stat	file_stat;

	if (ft_strncmp(list->cmd_args[0], ".", 2) == 0)
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		mid_free_exit(2, env, list->root);
	}
	if (access(list->cmd_args[0], F_OK) != 0)
	{
		putstr_fd("minishell: ", list->cmd_args[0],
			" : No such file or directory\n", 2);
		mid_free_exit(127, env, list->root);
	}
	if (access(list->cmd_args[0], X_OK | R_OK | W_OK) != 0)
	{
		putstr_fd("minishell: ", list->cmd_args[0], " : Permission denied\n",
			2);
		mid_free_exit(126, env, list->root);
	}
	if (stat(list->cmd_args[0], &file_stat) == 0)
	{
		if (S_ISREG(file_stat.st_mode))
			return (0);
		else
		{
			putstr_fd("minishell: ", list->cmd_args[0], " : is a directory\n",
				2);
			mid_free_exit(126, env, list->root);
		}
	}
	return (0);
}

void	exec_cmd(t_msh *list, t_env **env)
{
	char	**env_arr;
	int		check;

	check = 1;
	env_arr = NULL;
	env_arr = get_env_arr(env);
	if (list->cmd_args[0] == NULL)
		mid_free_exit(0, env, list);
	if (list->cmd_args[0][0] == '.' || list->cmd_args[0][0] == '/')
		check = check_dot(list, env);
	if (list->cmd_path == NULL && check == 0)
	{
		list->cmd_path = malloc(sizeof(char) * (ft_strlen(list->cmd_args[0]))
				+ 1);
		ft_strlcpy(list->cmd_path, list->cmd_args[0],
			ft_strlen(list->cmd_args[0]) + 1);
	}
	execve(list->cmd_path, list->cmd_args, env_arr);
	putstr_fd("minishell: ", list->cmd_args[0], ": command not found\n", 2);
	// stick to syntax 👹
	free_env_arr(env_arr);
	mid_free_exit(127, env, list);
}
