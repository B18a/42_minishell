/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ajehle_copy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:48:53 by andreasjehl       #+#    #+#             */
/*   Updated: 2024/04/06 15:15:06 by ajehle           ###   ########.fr       */
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

void	ft_print_msh(t_msh *msh)
{
	int	i;

	i = 0;
	ft_printf("--------PRINT MSH:-------------\n");
	while (msh)
	{
		ft_printf("ELEMENT	:	%i\n",i);
		ft_printf("TYPE	:	%s\n",return_true_type(msh->type));
		ft_printf("TOKEN	:	%s\n",msh->token);
		ft_printf("-------------------------------------------\n");
		ft_printf("\n");
		msh = msh->next;
		i++;
	}
}

t_msh	*ft_msh_new(void *content)
{
	t_msh	*new;

	new = (t_msh *)malloc(sizeof(t_msh));
	if (!new)
		return (NULL);
	new->token = content;
	new->next = NULL;
	return (new);
}

t_msh	*ft_msh_last(t_msh *lst)
{
	if (!lst)
		return (NULL);
	if (!(lst->next))
		return (lst);
	else
		return (ft_msh_last(lst->next));
}

void	ft_msh_add_front(t_msh **lst, t_msh *new)
{
	if (new == NULL)
		return ;
	else
	{
		new->next = lst[0];
		lst[0] = new;
	}
}

void	ft_msh_add_back(t_msh **lst, t_msh *new)
{
	if (!*lst)
		ft_msh_add_front(lst, new);
	else
		ft_msh_last(*lst)->next = new;
}

char	*copy_token(char *str, int i)
{
		ft_printf("START\n");
		ft_printf("%s\n", str);
	int	start;
	int	len;
	char *token;

	len = 1;
	token = NULL;
	if(str[i] && str[i] == ' ')
		i++;
	start = i;
	while ((str[i] != '<' || str[i] != '>' || str[i] != ' ') && str[i])
	{
		i++;
		len++;
	}
	ft_printf("len	%i\n", len);
	token = ft_calloc(len, sizeof(char));
	if(!token)
		return(NULL);
	ft_printf("start:%i\n", start);
	while(start)
	{
		str++;
		start--;
	}
	ft_strlcpy(token, str, len);
	ft_printf("TOKEN:%s\n", token);
	return (token);
}

t_msh	*fill_msh_lst(char *line)
{
	int	i = 0;
	t_msh	*start;
	t_msh	*new;
	start = ft_msh_new(0);
	if(!start)
	{
		ft_printf("Allocation of msh start failed\n");
	}
	int		open_quotes = FALSE;
	int		command = 0;
	char	*token = NULL;
	// start->next = NULL;
	// start->token = NULL;
	// start->type = 0;
	while(line[i])
	{
		if(line[i] && line[i + 1] && line[i] == '>' && line[i + 1] =='>')
		{
			ft_printf(">>\n");
			command = APPEND;
			token = copy_token(line, i+2);
		}
		else if(line[i] && line[i + 1] && line[i] == '<' && line[i + 1] == '<')
		{
			ft_printf("<<\n");
			command = HEREDOC;
			token = copy_token(line, i+2);
		}
		else if(line[i] == '>')
		{
			ft_printf(">\n");
			command = OUTFILE;
			token = copy_token(line, i+1);
		}
		else if(line[i] == '<')
		{
			ft_printf("<\n");
			command = INFILE;
			token = copy_token(line, i+1);
		}
		new = ft_msh_new(token);
		new->type = command;
		ft_msh_add_back(&start, new);
		i++;
	}
	return (start);
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
	t_msh	*msh;
	msh = fill_msh_lst(line);
	ft_print_msh(msh);
	// char **tokens = ft_split(line, '|');
	// if(!tokens)
	// {
	// 	printf("ARG IS EMPTY\n");
	// }
	// print_2d_arr(tokens);

	// t_minishell *start;
	// start = fill_lst(tokens);

	// free_lst(start);
	// free_2d_arr(tokens);
	// if(line)
	// 	free(line);

	return(0);
}
