/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:43:00 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/18 11:48:38 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/include/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <limits.h>


#define BLUE "\033[0;34m"
#define RESET "\033[0m"
#define RED "\033[0;31m"

# define BUFFER_SIZE 42

# define TRUE 1
# define FALSE 0

# define RIGHT 1
# define LEFT 0

#define p_read 0		//pipe fd[0] read
#define p_write 1		//pipe fd[1] write

# define ARG 1
# define QUOTE 2
# define DQUOTE 3
# define REDIRECT 4
# define PIPE 5

# define INFILE 30  // <
# define OUTFILE 40 // >
# define APPEND 50  // >>
# define HEREDOC 60 // <<

# define CMD 70
# define BUILTIN 80


// int stdin_cpy;
// int stdout_cpy;


typedef struct s_input
{
	char			*line;
	int				len;
	int				i;
}					t_input;

typedef struct s_tok
{
	int				type;
	int				syntax_error;
	char			*content;
	struct s_tok	*next;

}					t_tok;

typedef struct s_tok_ps
{
	int				type;
	int				syntax_error;
	char			**content;
	struct s_tok_ps	*next;

}					t_tok_ps;

typedef struct s_msh
{
	int				type;
	struct s_msh	*left;
	struct s_msh	*right;
	struct s_msh	*root;
	char			**cmd_args;
	char			*cmd_path;


	int				stdin_cpy;
	int				stdout_cpy;
	char			*exec;
}					t_msh;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}				t_env;

// debug
char				*return_true_type(int type);
void				ft_print_tok(t_tok *tok);
void				print_2d_arr(char **arr);

// free
void	free_tree(t_msh *root);
void	free_args(char	**args);

// get_input
void				free_mem(t_tok *tok);
int					check_for_buildins(char *str);
void				handle_tokens(t_tok *tok, int exit_code, t_env **env);

// get path
char				*get_path(char *argv);
void				free_old_path(char **exe_path);
char				*ft_strjoin_free(char *str, char *str2);

// parser_helper
int					is_redirect(int type);
int					is_option(char *c);
int					is_cmd(char *arg);
char				*ft_join_with_space(char const *s1, char const *s2);
int					get_pipes(t_tok *tok);

// parser_tree
t_msh				*create_new(int type, char *content);
t_msh				*make_branch(t_tok **tok);

// parser_tree_helper
char				**ft_split_first_word(char	*str, char c);
char				*ft_join_without_space(char const *s1, char const *s2);
char				*combine_cmd(char *old, char *add, int type);
char				*ft_strdup_space(const char *s1);
char				*erase_space(char *str);


// parser_no_pipe
t_msh				*fill_without_pipe(t_tok *tok);

// parser_pipes
t_msh				*create_pipes(int pipes);
t_msh				*fill_with_pipes(t_tok *tok, int pipes_total);

// parser
t_msh				*parsing(t_tok *tok);

// print_tree
void				print_tree_rec(t_msh *root, int level);
void				print_tree(t_msh *root);
void				print_tabs(int tabs);

// shell
void				get_input(t_env **env);

// sorting
void				swap_begin_of_tree(t_msh **start, t_msh **root);
void				swap_mid_of_tree(t_msh **prev, t_msh **root);
t_msh				*sort_tree_without_pipe(t_msh *root);
void				sort_tree_with_pipes(t_msh *root, int pipes_total);

// tokenizer helper 2
int					is_space(char c);
int					skip_spaces(char *argv, int i);
int					is_special_char(char c);
int					is_quote(char c);
int					is_unique_char(char c);

// tokenizer helper
t_tok				*ft_tok_new(char *content, int type);
t_tok				*ft_tok_last(t_tok *lst);
void				ft_tok_add_front(t_tok **lst, t_tok *new);
void				ft_tok_add_back(t_tok **lst, t_tok *new);

// tokenizer
char				*quote_string(t_input *input, int quote);
int					redirect_type(t_input *input);
char				*normal_string(t_input *input);
t_tok				*tokenizer(char *argv);

// expander
char				*ft_expand(char *argv, t_env **env, int type, int exit_code);
char				*get_res(char *argv, t_env **env, char *res, int exit_code);
int					get_res_len(char *argv, t_env **env, int exit_code);

// expander helper
void				increase_values(int *a, int *b);
void				init_values(int *a, int *b);
int					is_allowed_char(char c);

// exec
int					minishell_exec(t_msh *list, t_env **env);

int					handler(t_msh *list, int if_exit, t_env **env);
void				exec_pipe_write(int pipe_read, int pipe_write);
void				exec_pipe_read(int pipe_read, int pipe_write);
void				exec_cmd(t_msh *list, t_env **env);
void				exec_last_cmd(t_msh *list, int if_exit, t_env **env, int pid, int pipe_read, int pipe_write);
int					exec_outfile(t_msh *list, int if_exit, t_env **env);
int					exec_infile(t_msh *list, int if_exit, t_env **env);
int					exec_heredoc(t_msh *list, int if_exit, t_env **env);
int					exec_append(t_msh *list, int if_exit, t_env **env);
int					exec_builtin(t_msh *list, int if_exit, t_env **env);


// get_next_line
char				*get_next_line(int fd);


// free
void				mid_free_exit_child(int exit_code, t_env ** env, t_msh *list);

// env helper funktions
t_env				*get_env(char **env_start);
void				env_free(t_env *env);
void				env_lstadd_back(t_env **lst, t_env *new);
t_env				*env_lstlast(t_env *lst);
void				env_lstadd_front(t_env **lst, t_env *new);
char				*get_key(char *argv);
char				*expander(char *key, t_env **env);
int					ft_shell_lvl(t_env **env);
char				*expander_pre_exec(t_env **env, char *argv);

// builtins
int					ft_env(t_env **env, char **argv);
int					ft_export(t_env **env, char *argv);
int					ft_export_no_args(t_env **env);
int					ft_unset(t_env **env, char *argv);
int					ft_cd(t_env **env, char *dir);
int					ft_pwd(void);
int					ft_echo(char **argv);
int					ft_exit(char **argv, t_env **env, t_msh *list, int i);

void				open_quotes(t_input *input, char quote);
void				mid_free_exit(int exit_code, t_env ** env, t_msh *root);
void				putstr_fd(char *s1, char *s2, char *s3, int fd);



t_tok	*tokenizer_psanger(char *argv, t_env **env, int exit_code);
void	combine_tokens(t_tok *tok);
char	**split_with_quotes(char *argv, char c);
char	**join_two_d_arr(char **str1, char **str2);

char	**cpy_two_d_arr(int len, char **str1, char **str2);
int		get_two_d_arr_len(char **str1, char **str2);


#endif

