/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_psanger.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:36:10 by ajehle            #+#    #+#             */
/*   Updated: 2024/04/06 14:29:14 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PSANGER_H
# define MINISHELL_PSANGER_H

# include "../include/minishell.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>

# include "minishell_ajehle.h"
# include "minishell_psanger.h"

#define TRUE 1
#define FALSE 0

// type
// #define PIPE_WRITE 9
#define PIPE 10
// #define PIPE_READ 11

#define CMD 20

#define INFILE 30 // <
#define OUTFILE 40 // >
#define APPEND 50 // >>
#define HEREDOC 60 // <<

#define BUILDIN 70

typedef struct s_value
{
	char	*buildin;// -> typ builin

	char	*cmd;   // -> cmd           ls
	char	**cmd_args; // -> cmd + text    args[0] = "ls" args[1] = "-la" args[2] = NULL

	char	*name; // -> typ redirect
	bool	exec;// -> typ redirect

	bool	error;// if the given prompt is faulty
}			t_value;



typedef struct s_minishell
{
	int					type;
	struct s_minishell	*next;
	struct s_value		*value;
}						t_minishell;

typedef struct s_msh
{
	int				type;
	char			*token;
	struct s_msh	*next;

}					t_msh;

char		*get_path(char *argv);
t_minishell	*get_list();
void		minishell_exec(t_minishell *list);
void		exec_pipe_write(t_minishell *list, int *fd);
void		exec_pipe_read(t_minishell *list, int *fd);
void		exec_cmd(t_minishell *list);
void		exec_outfile(t_minishell *list);
void		exec_infile(t_minishell *list);
void		exec_append(t_minishell *list);

#endif

// wir brauchen beim parcing eine hirachie der einzenen teile (Infile, Outfile, Cmd, Pipe...)
// zuerst Pipe
// dann Inflile, Outfile, Append, Heredoc
// dann cmd und buildin
// man könnte einen token string machen und dann anhand diesem die liste so anordnen wie man es braucht.
