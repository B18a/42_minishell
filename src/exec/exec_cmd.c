/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:10:19 by psanger           #+#    #+#             */
/*   Updated: 2024/05/11 00:44:08 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	exec_last_cmd(t_msh *list, int if_exit, t_env **env, int pid, int pipe_read, int pipe_write)
// {
// 	int	exit_code;
// 	int pid2;

// 	pid2 = 0;
// 	exit_code = 0;
// 	pid2 = fork();
// 	if (pid2 < 0) {
// 		write(2, "ERROR CREATE PIPE\n", 19);
// 		exit(1);
// 	}
// 	if (pid2 == 0) {
// 		exec_pipe_read(pipe_read, pipe_write);
// 		handler(list, if_exit, env);
// 	}
// 	if (pid2 > 0) {
// 		// close(pipe_read);
// 		// close(pipe_write);
// 		waitpid(pid, &exit_code, 0);
// 		waitpid(pid2, &exit_code, 0);
// 	}
// 	exit(exit_code);
// }

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


void	exec_cmd(t_msh *list, t_env **env)
{
	char **env_arr;

	env_arr = NULL;
	env_arr = get_env_arr(env);
	if (list->cmd_path == NULL) {
		list->cmd_path = malloc(sizeof(char) * (ft_strlen(list->cmd_args[0])) + 1);
		ft_strlcpy(list->cmd_path, list->cmd_args[0], ft_strlen(list->cmd_args[0]) + 1);
	}
	// fprintf(stderr, "|%s|\n",list->cmd_args[1]);
	if (execve(list->cmd_path, list->cmd_args, env_arr) == -1)
	{
		write(2, "minishell: ", 12);
		ft_putstr_fd(list->cmd_args[0], 2);
		write(2, ": stick to syntax 👹\n", 24);
		free_env_arr(env_arr);
		mid_free_exit(127, env, list);
	}
	exit(1);
}
