/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ajehle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:48:53 by andreasjehl       #+#    #+#             */
/*   Updated: 2024/04/04 11:38:29 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



t_minishell	*testf(void)
{
	t_minishell	*lst0;
	lst0 = set_mem_lst();
	lst0->type = PIPE_WRITE;

	t_minishell *lst1;
	lst1 = set_mem_lst();

	lst0->next = lst1;
	lst1->type = CMD;
	lst1->value->cmd = "grep";
	lst1->value->cmd_args = ft_split("abaabaaabaaaabaaaaabaaaaaa", 'b');
	// lst1->value->cmd_args[0] = "grep";
	// lst1->value->cmd_args[1] = "exec";
	// lst1->value->cmd_args[2] = NULL;

	// t_minishell *list2 = malloc(sizeof(t_minishell));
	// null_struct(list2);
	// list1->next = list2;
	// list2->type = INFILE;
	// list2->value->name = "test_in_yes";
	// t_minishell *list3 = malloc(sizeof(t_minishell));
	// null_struct(list3);
	// list2->next = list3;
	// list3->type = PIPE_READ;
	// t_minishell *list4 = malloc(sizeof(t_minishell));
	// null_struct(list4);
	// list3->next = list4;
	// list4->type = APPEND;
	// list4->value->name = "outfile";
	// t_minishell *list5 = malloc(sizeof(t_minishell));
	// null_struct(list5);
	// list4->next = list5;
	// list5->type = CMD;
	// list5->value->cmd_args[0] = "wc";
	// list5->value->cmd_args[1] = "-l";
	// list5->value->cmd_args[2] = NULL;
	// list5->value->cmd = list5->value->cmd_args[0];



	return (lst0);
}



int	run_andi_main(int argc, char **argv)
{
	// char *line;

	// line = NULL;
	printf("%i,  %s\n",argc, argv[0]);
	// while(1)
	// {
	// 	line = readline("minishell:");
	// 	if(line)
	// 		break;
	// }
	// printf("YOU WROTE : %s",line);
	// if(line)
	// 	free(line);
	t_minishell *test;

	test = testf();
	printf_list(test);
	free_lst(test);

	return(0);
}
