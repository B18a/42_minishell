/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ajehle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:38:45 by ajehle            #+#    #+#             */
/*   Updated: 2024/03/28 12:20:44 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"


void	get_input(void)
{
	char *line;

	line = NULL;
	while(1)
	{
		line = readline("minishell:");
		if(line)
		{
			add_history(line);
			if(line)
				free(line);
		}
	}
}

void	get_current_work_dir(void)
{
	char wd[100];
	getcwd(wd, 50);
	printf("CWD : %s",wd);
}

static void	signal_handler(int signum)
{
	printf("PID %i\n",getpid());
	printf("NBR IS %i\n",signum);
	if(signum == 2)	//CTRL-C
	{

	}
	if(signum == 3)	//CTRL-Backslash
	{

	}
}


int	run_andi_main(void)
{
	signal(SIGINT, signal_handler);		//CTRL-C
	// signal(???, signal_handler);	//CTRL-D?
	signal(SIGQUIT, signal_handler);	//CTRL-Backslash

	get_input();
	get_current_work_dir();
	return(0);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <signal.h>

// // Signal handler function for Ctrl-C (SIGINT)
// void sigint_handler(int signum) {
//     printf("Custom Ctrl-C behavior: SIGINT received. Exiting.\n");
//     exit(EXIT_SUCCESS);
// }

// // Signal handler function for Ctrl-D (EOF)
// void eof_handler(int signum) {
//     printf("Custom Ctrl-D behavior: EOF received. Ignoring.\n");
// }

// int main() {
//     // Register the signal handler for SIGINT (Ctrl-C)
//     if (signal(SIGINT, sigint_handler) == SIG_ERR) {
//         perror("Unable to register SIGINT handler");
//         exit(EXIT_FAILURE);
//     }

//     // Register the signal handler for EOF (Ctrl-D)
//     if (signal(SIGQUIT, eof_handler) == SIG_ERR) {
//         perror("Unable to register EOF handler");
//         exit(EXIT_FAILURE);
//     }

//     printf("Press Ctrl-C or Ctrl-D to trigger custom behavior:\n");

//     // Infinite loop to keep the program running
//     while (1) {
//         // Do nothing, just keep the program running
//     }

//     return 0;
// }
