/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ajehle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:48:53 by andreasjehl       #+#    #+#             */
/*   Updated: 2024/04/04 11:50:47 by ajehle           ###   ########.fr       */
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
	lst1->value->cmd_args = ft_split("grep exec", ' ');
	lst1->value->cmd = lst1->value->cmd_args[0];

	t_minishell *lst2;
	lst2 = set_mem_lst();
	lst1->next = lst2;
	lst2->type = INFILE;
	lst2->value->name = "test_in_yes";

	t_minishell *lst3;
	lst3 = set_mem_lst();
	lst2->next = lst3;
	lst3->type = PIPE_READ;

	t_minishell *lst4;
	lst4 = set_mem_lst();
	lst3->next = lst4;
	lst4->type = APPEND;
	lst4->value->name = "outfile";

	t_minishell *lst5;
	lst5 = set_mem_lst();
	lst4->next = lst5;
	lst5->type = CMD;
	lst5->value->cmd_args = ft_split("wc -l", ' ');
	lst5->value->cmd = lst5->value->cmd_args[0];

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
