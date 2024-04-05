/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ajehle.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:36:10 by ajehle            #+#    #+#             */
/*   Updated: 2024/04/04 15:54:41 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_AJEHLE_H
# define MINISHELL_AJEHLE_H

# include "minishell_ajehle.h"
# include "minishell_psanger.h"

# include<readline/readline.h>
# include<readline/history.h>



// debug
void	print_2d_arr(char **arr);
void	printf_list(t_minishell *lst);
char	*return_true_type(int type);

// preset
void	preset_struct(t_minishell *lst);

// set mem
t_minishell	*set_mem_lst(void);


// free mem
void	free_value(t_value *value);
void	free_lst(t_minishell *lst);
void	free_2d_arr(char	**arr);



// main

int	run_andi_main(int argc, char **argv);


#endif
