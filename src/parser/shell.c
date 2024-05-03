/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 11:39:23 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/03 16:00:58 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_c_handler()
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
	// int in = dup(STDIN_FILENO);
	// int out = dup(STDOUT_FILENO);

	// // t_msh *cmd_left1 = malloc(sizeof(t_msh));
	// // null_struct_2(cmd_left1, in, out);
	// // cmd_left1->type = BUILTIN;
	// // cmd_left1->cmd_args = malloc(sizeof(char *) * 3);
	// // cmd_left1->cmd_args[0] = "export";
	// // cmd_left1->cmd_args[1] = NULL;

	// // t_msh *outfile_1 = malloc(sizeof(t_msh));
	// // null_struct_2(outfile_1, in, out);
	// // outfile_1->type = OUTFILE;
	// // outfile_1->cmd_args = malloc(sizeof(char *) * 2);
	// // outfile_1->cmd_args[0] = "test1";
	// // outfile_1->cmd_args[1] = NULL;
	// // outfile_1->exec = TRUE;

	// t_msh *pipe = malloc(sizeof(t_msh));
	// null_struct_2(pipe, in, out);
	// pipe->type = PIPE;
	// pipe->cmd_args = NULL;
	// pipe->exec = NULL;
	// pipe->left = NULL;
	// pipe->right = NULL;

	// t_msh *cmd_left1 = malloc(sizeof(t_msh));
	// null_struct_2(cmd_left1, in, out);
	// cmd_left1->type = CMD;
	// cmd_left1->cmd_args = malloc(sizeof(char *) * 2);
	// cmd_left1->cmd_args[0] = "cat";
	// cmd_left1->cmd_args[1] = NULL;
	// cmd_left1->cmd_path = get_path(cmd_left1->cmd_args[0]);


	// t_msh *cmd_left2 = malloc(sizeof(t_msh));
	// null_struct_2(cmd_left2, in, out);
	// cmd_left2->type = CMD;
	// cmd_left2->cmd_args = malloc(sizeof(char *) * 2);
	// cmd_left2->cmd_args[0] = "cat";
	// cmd_left2->cmd_args[1] = "h";
	// cmd_left2->cmd_args[1] = NULL;
	// cmd_left2->cmd_path = get_path(cmd_left2->cmd_args[0]);


	// pipe->left = cmd_left1;
	// pipe->right = cmd_left2;

	// return (pipe);


int	main(int argc, char **argv, char **env_start)
{
	t_env *env;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_c_handler);
	if (argc != 1)
	{
		printf("%s, wrong num args\n", argv[0]);
		return (0);
	}
	env = get_env(env_start);
	ft_shell_lvl(&env);
	// t_msh *test = get_list_2();


	get_input(&env);
	// minishell_exec(test, &env);
	// expander("PWD", env);
	return (0);
}
