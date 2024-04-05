/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ajehle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:48:53 by andreasjehl       #+#    #+#             */
/*   Updated: 2024/04/05 15:43:42 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// t_minishell	*testf(void)
// {
// 	t_minishell	*lst0;
// 	lst0 = set_mem_lst();
// 	lst0->type = PIPE_WRITE;

// 	t_minishell *lst1;
// 	lst1 = set_mem_lst();
// 	lst0->next = lst1;
// 	lst1->type = CMD;
// 	lst1->value->cmd_args = ft_split("grep exec", ' ');
// 	lst1->value->cmd = lst1->value->cmd_args[0];

// 	t_minishell *lst2;
// 	lst2 = set_mem_lst();
// 	lst1->next = lst2;
// 	lst2->type = INFILE;
// 	lst2->value->name = "test_in_yes";

// 	t_minishell *lst3;
// 	lst3 = set_mem_lst();
// 	lst2->next = lst3;
// 	lst3->type = PIPE_READ;

// 	t_minishell *lst4;
// 	lst4 = set_mem_lst();
// 	lst3->next = lst4;
// 	lst4->type = APPEND;
// 	lst4->value->name = "outfile";

// 	t_minishell *lst5;
// 	lst5 = set_mem_lst();
// 	lst4->next = lst5;
// 	lst5->type = CMD;
// 	lst5->value->cmd_args = ft_split("wc -l", ' ');
// 	lst5->value->cmd = lst5->value->cmd_args[0];

// 	return (lst0);
// }

int is_separator(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return(1);
	else
		return(0);
}


char	*delimit_string(char *str)
{
	char	*ret;
	int i = 0;
	int j = 0;
	ret = ft_calloc(sizeof(char), ft_strlen(str));
	if (!ret)
		return (NULL);
	while(is_separator(str[i]) && str[i])
		i++;
	while(str[i])
	{
		while(is_separator(str[i]) && str[i])
			i++;
		if(!is_separator(str[i]) && str[i])
		{
			ret[j] = str[i];
			j++;
			if(is_separator(str[i + 1]) && str[i + 1])
			{
				ret[j] = ' ';
				j++;
			}
		}
		i++;
	}
	return (ret);
}

int	check_redirects(char *temp, t_minishell *lst)
{
		if(!ft_strncmp(temp,"<<",2))
			lst->type = APPEND;
		else if(!ft_strncmp(temp,">>",2))
			lst->type = HEREDOC;
		else if(!ft_strncmp(temp,"<",1))
			lst->type = INFILE;
		else if(!ft_strncmp(temp,">",1))
			lst->type = OUTFILE;
		if(lst->type)
		{
			lst->value->name = temp++;
			lst->value->exec = TRUE;
			return (1);
		}
		return (0);
}

int	check_pipe(char *temp, t_minishell *lst)
{


}

t_minishell *set_values(char *token)
{
	t_minishell	*lst;
	char		**temp;
	int			i = 0;

	lst = set_mem_lst();
	if (!lst)
		return (NULL);
	if (token)
	{
		temp = NULL;
		i = 0;
		temp = ft_split(token, ' ');
		while (temp[i])
		{
			ft_printf("[%i]%s\n",i,temp[i]);
			if(check_redirects(temp[i], lst))
				i++;
			else if(check_pipe(temp[i],lst))
			{
				ft_printf("PIPE \n");

			}
				// ft_printf("REDIRECT \n");
			// else
				// ft_printf("NO REDIRECT \n");
			i++;
		}
		if(temp)
			free(temp);
	}
	return (lst);
}

int	count_pipes(char **tokens)
{
	int	i;

	i = 0;
	while(tokens && tokens[i])
		i++;
	i--;
	return (i);
}

t_minishell	*fill_lst(char	**tokens)
{
	t_minishell	*begin;
	// char		*single_token;
	int			i;
	int			pipes;


	begin = set_mem_lst();
	if (!begin)
		return (NULL);
	i = 0;
	pipes = count_pipes(tokens);
	ft_printf("PIPES %i\n\n",pipes);
	// if(pipes)
	// {
	// 	// generate first msh struct
	// 	// lst add front?
	// }

	while (tokens && tokens[i])
	{
		if (i > 0)
		{
			// create a msh strct with pipe
		}
		tokens[i] =	delimit_string(tokens[i]);
		ft_printf("[%i]->%s\n\n",i,tokens[i]);
		// analyse piece of chunk and set to bits that can be handled
		begin = set_values(tokens[i]);
		i++;
	}
	ft_printf("\n");
	return (begin);
}


int	run_andi_main(int argc, char **argv)
{
	printf("%i,  %s\n",argc, argv[0]);
	char *line;

	line = NULL;
	while(1)
	{
		line = readline("minishell:");
		if(line)
			break;
	}
	char **tokens = ft_split(line, '|');
	if(!tokens)
	{
		printf("ARG IS EMPTY\n");
	}
	print_2d_arr(tokens);

	t_minishell *start;
	start = fill_lst(tokens);
	printf_list(start);

	// free_lst(start);
	// free_2d_arr(tokens);
	// if(line)
	// 	free(line);

	return(0);
}
