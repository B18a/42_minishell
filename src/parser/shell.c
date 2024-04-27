/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 11:39:23 by ajehle            #+#    #+#             */
/*   Updated: 2024/04/27 13:25:58 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	null_struct_2(t_msh *list, int in, int out)
{
	list->stdin_cpy = in;
	list->stdout_cpy = out;
	list->right = NULL;
	list->left = NULL;
	list->type = FALSE;
}


t_msh *get_list_2()
{
	int in = dup(STDIN_FILENO);
	int out = dup(STDOUT_FILENO);


	t_msh *pipe1 = malloc(sizeof(t_msh));
	null_struct_2(pipe1, in, out);
	pipe1->type = PIPE;
	pipe1->cmd_args = malloc(sizeof(char *) * 1);;
	pipe1->cmd_args[0] = NULL;
	pipe1->exec = TRUE;

	t_msh *pipe2 = malloc(sizeof(t_msh));
	null_struct_2(pipe2, in, out);
	pipe2->type = PIPE;
	pipe2->cmd_args = malloc(sizeof(char *) * 1);;
	pipe2->cmd_args[0] = NULL;
	pipe2->exec = TRUE;

	t_msh *cmd1 = malloc(sizeof(t_msh));
	null_struct_2(cmd1, in, out);
	cmd1->type = CMD;
	cmd1->cmd_args = malloc(sizeof(char *) * 2);
	cmd1->cmd_args[0] = "ls";
	cmd1->cmd_args[1] = NULL;
	cmd1->exec = TRUE;
	cmd1->cmd_path = get_path(cmd1->cmd_args[0]);

	t_msh *cmd_left1 = malloc(sizeof(t_msh));
	null_struct_2(cmd_left1, in, out);
	cmd_left1->type = CMD;
	cmd_left1->cmd_args = malloc(sizeof(char *) * 3);
	cmd_left1->cmd_args[0] = "grep";
	cmd_left1->cmd_args[1] = "l";
	cmd_left1->cmd_args[2] = NULL;
	cmd_left1->cmd_path = get_path(cmd_left1->cmd_args[0]);

	t_msh *outfile1 = malloc(sizeof(t_msh));
	null_struct_2(outfile1, in, out);
	outfile1->type = OUTFILE;
	outfile1->cmd_args = malloc(sizeof(char *) * 3);
	outfile1->cmd_args[0] = "file";
	outfile1->cmd_args[1] = NULL;

	pipe1->left = cmd1;
	pipe1->right = pipe2;
	pipe2->left = cmd_left1;
	pipe2->right = outfile1;

	return (pipe1);
}

int	main(void)
{
	get_input();
	// print_tree(get_list_2());
	// minishell_exec(get_list_2());
	return (0);
}
