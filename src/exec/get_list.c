/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:05:05 by psanger           #+#    #+#             */
/*   Updated: 2024/04/11 01:13:13 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	null_struct(t_minishell *list)
{
	list->right = NULL;
	list->left = NULL;
	list->type = FALSE;
	list->value = malloc(sizeof(t_value));
	list->value->cmd = NULL;
	list->value->cmd_args = NULL;
	list->value->exec = FALSE;
	list->value->name = NULL;
}


t_minishell *get_list_sleep()
{
	t_minishell *first_pipe = malloc(sizeof(t_minishell));
	first_pipe->right = NULL;
	first_pipe->left = NULL;
	first_pipe->value = NULL;
	first_pipe->type = PIPE;

	t_minishell *cmd_left1 = malloc(sizeof(t_minishell));
	null_struct(cmd_left1);
	cmd_left1->type = CMD;
	cmd_left1->value->cmd = "sleep";
	cmd_left1->value->cmd_args = malloc(sizeof(char *) * 3);
	cmd_left1->value->cmd_args[0] = cmd_left1->value->cmd;
	cmd_left1->value->cmd_args[1] = "5";
	cmd_left1->value->cmd_args[2] = NULL;

	t_minishell *second_pipe = malloc(sizeof(t_minishell));
	second_pipe->right = NULL;
	second_pipe->left = NULL;
	second_pipe->value = NULL;
	second_pipe->type = PIPE;

	t_minishell *cmd_left2 = malloc(sizeof(t_minishell));
	null_struct(cmd_left2);
	cmd_left2->type = CMD;
	cmd_left2->value->cmd = "sleep";
	cmd_left2->value->cmd_args = malloc(sizeof(char *) * 3);
	cmd_left2->value->cmd_args[0] = cmd_left2->value->cmd;
	cmd_left2->value->cmd_args[1] = "3";
	cmd_left2->value->cmd_args[2] = NULL;

	t_minishell *third_pipe =  malloc(sizeof(t_minishell));
	third_pipe->right = NULL;
	third_pipe->left = NULL;
	third_pipe->value = NULL;
	third_pipe->type = PIPE;

	t_minishell *cmd_left3 = malloc(sizeof(t_minishell));
	null_struct(cmd_left3);
	cmd_left3->type = CMD;
	cmd_left3->value->cmd = "sleep";
	cmd_left3->value->cmd_args = malloc(sizeof(char *) * 3);
	cmd_left3->value->cmd_args[0] = cmd_left3->value->cmd;
	cmd_left3->value->cmd_args[1] = "1";
	cmd_left3->value->cmd_args[2] = NULL;

	first_pipe->left =  cmd_left1;
	first_pipe->right = second_pipe;

	second_pipe->left = cmd_left2;
	second_pipe->right = cmd_left3;

	return (first_pipe);
}



void	null_struct_2(t_minishell *list, int in, int out)
{
	list->stdin_cpy = in;
	list->stdout_cpy = out;
	list->right = NULL;
	list->left = NULL;
	list->type = FALSE;
	list->value = malloc(sizeof(t_value));
	list->value->cmd = NULL;
	list->value->cmd_args = NULL;
	list->value->exec = FALSE;
	list->value->name = NULL;
}

t_minishell *get_list_2()
{
	int in = dup(STDIN_FILENO);
	int out = dup(STDOUT_FILENO);


	t_minishell *first_pipe = malloc(sizeof(t_minishell));
	first_pipe->right = NULL;
	first_pipe->left = NULL;
	first_pipe->value = NULL;
	first_pipe->type = PIPE;



	// t_minishell *outfile_1 = malloc(sizeof(t_minishell));
	// null_struct(outfile_1);
	// outfile_1->type = OUTFILE;
	// outfile_1->value->name = "test1";
	// outfile_1->value->exec = TRUE;

	t_minishell *cmd_left1 = malloc(sizeof(t_minishell));
	null_struct_2(cmd_left1, in, out);
	cmd_left1->type = CMD;
	cmd_left1->value->cmd = "ls";
	cmd_left1->value->cmd_args = malloc(sizeof(char *) * 3);
	cmd_left1->value->cmd_args[0] = cmd_left1->value->cmd;
	cmd_left1->value->cmd_args[1] = "-la";
	cmd_left1->value->cmd_args[1] = NULL;



	t_minishell *second_pipe = malloc(sizeof(t_minishell));
	second_pipe->right = NULL;
	second_pipe->left = NULL;
	second_pipe->value = NULL;
	second_pipe->type = PIPE;





	t_minishell *heredoc = malloc(sizeof(t_minishell));
	null_struct_2(heredoc, in, out);
	heredoc->type = HEREDOC;
	heredoc->value->name = "END";
	heredoc->value->exec = TRUE;

	t_minishell *cmd_left2 = malloc(sizeof(t_minishell));
	null_struct_2(cmd_left2, in, out);
	cmd_left2->type = CMD;
	cmd_left2->value->cmd = "grep";
	cmd_left2->value->cmd_args = malloc(sizeof(char *) * 3);
	cmd_left2->value->cmd_args[0] = cmd_left2->value->cmd;
	cmd_left2->value->cmd_args[1] = "exec";
	cmd_left2->value->cmd_args[2] = NULL;

	t_minishell *third_pipe =  malloc(sizeof(t_minishell));
	third_pipe->right = NULL;
	third_pipe->left = NULL;
	third_pipe->value = NULL;
	third_pipe->type = PIPE;

	t_minishell *cmd_left3 = malloc(sizeof(t_minishell));
	null_struct_2(cmd_left3, in, out);
	cmd_left3->type = CMD;
	cmd_left3->value->cmd = "wc";
	cmd_left3->value->cmd_args = malloc(sizeof(char *) * 3);
	cmd_left3->value->cmd_args[0] = cmd_left3->value->cmd;
	cmd_left3->value->cmd_args[1] = "-l";
	cmd_left3->value->cmd_args[1] = NULL;

	t_minishell *cmd_right4 = malloc(sizeof(t_minishell));
	null_struct(cmd_right4);
	cmd_right4->type = CMD;
	cmd_right4->value->cmd = "wc";
	cmd_right4->value->cmd_args = malloc(sizeof(char *) * 3);
	cmd_right4->value->cmd_args[0] = cmd_right4->value->cmd;
	cmd_right4->value->cmd_args[1] = "5";
	cmd_right4->value->cmd_args[1] = NULL;


	first_pipe->left = cmd_left1;
	first_pipe->right = second_pipe;

	second_pipe->left = cmd_left2;
	second_pipe->right = third_pipe;

	third_pipe->left = cmd_left3;
	third_pipe->right = cmd_right4;


	return (first_pipe);
}


// t_minishell *get_list()
// {

// 	t_minishell *list_root = malloc(sizeof(t_minishell));
// 	list_root->next = NULL;
// 	list_root->value = NULL;
// 	list_root->type = PIPE_WRITE;

// 	t_minishell *first_pipe = malloc(sizeof(t_minishell));
// 	null_struct(first_pipe);
// 	first_pipe->type = INFILE;
// 	first_pipe->value->name = "test_in_yes";
// 	first_pipe->value->exec = TRUE;

// 	t_minishell *cmd_left1 = malloc(sizeof(t_minishell));
// 	null_struct(cmd_left1);
// 	cmd_left1->type = OUTFILE;
// 	cmd_left1->value->name = "test_yes";
// 	cmd_left1->value->exec = FALSE;

// 	t_minishell *list3 = malloc(sizeof(t_minishell));
// 	null_struct(list3);
// 	list3->type = CMD;
// 	list3->value->cmd = "grep";
// 	list3->value->cmd_args = malloc(sizeof(char *) * 3);
// 	list3->value->cmd_args[0] = list3->value->cmd;
// 	list3->value->cmd_args[1] = "exec";
// 	list3->value->cmd_args[2] = NULL;


// 	t_minishell *list4 = malloc(sizeof(t_minishell));
// 	list4->next = NULL;
// 	list4->value = NULL;
// 	list4->type = PIPE_READ;

// 	t_minishell *second_pipe = malloc(sizeof(t_minishell));
// 	null_struct(second_pipe);
// 	second_pipe->type = CMD;
// 	second_pipe->value->cmd = "wc";
// 	second_pipe->value->cmd_args = malloc(sizeof(char *) * 3);
// 	second_pipe->value->cmd_args[0] = list3->value->cmd;
// 	second_pipe->value->cmd_args[1] = "-l";
// 	second_pipe->value->cmd_args[2] = NULL;

// 	list_root->next = first_pipe;
// 	first_pipe->next = cmd_left1;
// 	cmd_left1->next = list3;
// 	list3->next = list4;
// 	list4->next = second_pipe;

// 	return (list_root);
// }


// t_minishell	*test()
// {
// 	t_minishell *list0 = malloc(sizeof(t_minishell));
// 	null_struct(list0);
// 	list0->type = PIPE_WRITE;

// 	t_minishell *first_pipe = malloc(sizeof(t_minishell));
// 	null_struct(first_pipe);
// 	list0->next = first_pipe;
// 	first_pipe->type = CMD;
// 	first_pipe->value->cmd = "grep";
// 	first_pipe->value->cmd_args[0] = "grep";
// 	first_pipe->value->cmd_args[1] = "exec";
// 	first_pipe->value->cmd_args[2] = NULL;

// 	t_minishell *cmd_left1 = malloc(sizeof(t_minishell));
// 	null_struct(cmd_left1);
// 	first_pipe->next = cmd_left1;
// 	cmd_left1->type = INFILE;
// 	cmd_left1->value->name = "test_in_yes";

// 	t_minishell *list3 = malloc(sizeof(t_minishell));
// 	null_struct(list3);
// 	cmd_left1->next = list3;
// 	list3->type = PIPE_READ;

// 	t_minishell *list4 = malloc(sizeof(t_minishell));
// 	null_struct(list4);
// 	list3->next = list4;
// 	list4->type = APPEND;
// 	list4->value->name = "outfile";

// 	t_minishell *second_pipe = malloc(sizeof(t_minishell));
// 	null_struct(second_pipe);
// 	list4->next = second_pipe;
// 	second_pipe->type = CMD;
// 	second_pipe->value->cmd_args[0] = "wc";
// 	second_pipe->value->cmd_args[1] = "-l";
// 	second_pipe->value->cmd_args[2] = NULL;
// 	second_pipe->value->cmd = second_pipe->value->cmd_args[0];


// }
