/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ajehle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreasjehle <andreasjehle@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:48:53 by andreasjehl       #+#    #+#             */
/*   Updated: 2024/03/27 23:24:49 by andreasjehl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_andi_main(int argc, char **argv)
{
	char *line;

	line = NULL;
	printf("%i,  %s\n",argc, argv[0]);
	while(1)
	{
		line = readline("minishell:");
		if(line)
			break;
	}
	printf("YOU WROTE : %s",line);
	return(0);
}