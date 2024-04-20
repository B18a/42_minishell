/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:04:46 by psanger           #+#    #+#             */
/*   Updated: 2024/04/18 17:54:09 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../../libs/libft/include/libft.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif


#define TRUE 1
#define FALSE 0

#define p_read 0		//pipe fd[0] read
#define p_write 1		//pipe fd[1] write

// type
#define PIPE_WRITE 9
#define PIPE 10
#define PIPE_READ 11

#define CMD 20
#define INFILE 30 // <
#define OUTFILE 40 // >
#define APPEND 50 // >>
#define HEREDOC 60 // <<
#define BUILTIN 70

typedef struct s_value
{
	int							*pipe;

	char						*buildin;// -> typ builin

	char						*cmd;	// -> cmd 			ls
	char						**cmd_args;	// -> cmd + text	args[0] = "ls" args[1] = "-la" args[2] = NULL

	char						*name; // -> typ redirect
	bool						exec;// -> typ redirect
}								t_value;

typedef struct s_minishell
{
	int							type;
	int							stdin_cpy;
	int							stdout_cpy;
	struct s_minishell			*right;
	struct s_minishell			*left;
	struct s_value				*value;
	// char						**cmd_args;	// -> cmd + text	args[0] = "ls" args[1] = "-la" args[2] = NULL
}								t_minishell;


void	handler(t_minishell *list);

char	*get_next_line(int fd);

char	*get_path(char *argv);
t_minishell *get_list();
t_minishell *get_list_2();
t_minishell *get_list_sleep();

void	minishell_exec(t_minishell *list);

void	exec_pipe_write(int pfd[2]);
void	exec_pipe_read(int pfd[2]);
void	exec_cmd(t_minishell *list);
void	exec_last_cmd(t_minishell *list);
void	exec_outfile(t_minishell *list);
void	exec_infile(t_minishell *list);
void	exec_heredoc(t_minishell *list);
void	exec_append(t_minishell *list);
void	exec_builtin(t_minishell *list);

#endif


// wir brauchen beim parcing eine hirachie der einzenen teile (Infile, Outfile, Cmd, Pipe...)
// zuerst Pipe
// dann Inflile, Outfile, Append, Heredoc
// dann cmd und buildin

// man könnte einen token string machen und dann anhand diesem die liste so anordnen wie man es braucht.

