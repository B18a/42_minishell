/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 11:39:23 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/10 23:28:01 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_c_handler(int signum)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	free_test(t_msh *test)
{
	if (test == NULL)
		return ;
	free_test(test->left);
	free_test(test->right);
	if (test->cmd_path)
		free(test->cmd_path);
	if (test->cmd_args)
		free(test->cmd_args);
	free(test);
}



t_msh	*get_list()
{

	t_msh *infile = malloc(sizeof(t_msh));
	infile->cmd_args = malloc(sizeof(char *) * 2);
	infile->cmd_args[0] = "file";
	infile->cmd_args[1] = NULL;
	infile->cmd_path = NULL;
	// infile->exec = "cat";
	infile->left = NULL;
	infile->right = NULL;
	infile->type = INFILE;


	t_msh *cmd1 = malloc(sizeof(t_msh));
	cmd1->cmd_args = malloc(sizeof(char *) * 3);
	cmd1->cmd_args[0] = "cat";
	cmd1->cmd_args[1] = "notes";
	cmd1->cmd_args[2] = NULL;
	cmd1->cmd_path = get_path(cmd1->cmd_args[0]);
	// cmd1->exec = "cat";
	cmd1->left = NULL;
	cmd1->right = NULL;
	cmd1->type = CMD;

	infile->left = cmd1;

	print_tree(infile);
	return (infile);
}



int	main(int argc, char **argv, char **env_start)
{
	t_env	*env;

	env = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_c_handler);
	if (argc != 1)
	{
		printf("%s, wrong num args\n", argv[0]);
		return (0);
	}
	env = get_env(env_start);
	ft_shell_lvl(&env);
	// minishell_exec(get_list(), &env);
	get_input(&env);
	env_free(env);
	return (0);
}
