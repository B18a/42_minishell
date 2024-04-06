/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ajehle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:48:53 by andreasjehl       #+#    #+#             */
/*   Updated: 2024/04/06 14:58:38 by ajehle           ###   ########.fr       */
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


int	check_pipe(char **temp,int i, t_minishell *lst)
{
	if(!ft_strncmp(temp[i],"|",1))
	{
		lst->type = PIPE;
		return (1);
	}
	return (0);
}

int	check_redirects(char **temp, int i, t_minishell *lst)
{
		if(!ft_strncmp(temp[i],"<<\0",3))
			lst->type = APPEND;
		else if(!ft_strncmp(temp[i],">>\0",3))
			lst->type = HEREDOC;
		else if(!ft_strncmp(temp[i],"<\0",2))
			lst->type = INFILE;
		else if(!ft_strncmp(temp[i],">\0",2))
			lst->type = OUTFILE;
		if(lst->type && temp[i + 1])
		{
			lst->value->name = temp[i + 1];
			lst->value->exec = TRUE;
			return (1);
		}
		return (0);
}


// t_minishell	*ft_msh_last(t_minishell *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	if (!(lst->next))
// 		return (lst);
// 	else
// 		return (ft_msh_last(lst->next));
// }

// void	ft_msh_add_front(t_minishell **lst, t_minishell *new)
// {
// 	if (new == NULL)
// 		return ;
// 	else
// 	{
// 		new->next = lst[0];
// 		lst[0] = new;
// 	}
// }

// void	ft_msh_add_back(t_minishell **lst, t_minishell *new)
// {
// 	if (!*lst)
// 		ft_msh_add_front(lst, new);
// 	else
// 		ft_msh_last(*lst)->next = new;
// }



// t_minishell	*fill_lst(char	**tokens)
// {
// 	t_minishell	*begin;
// 	t_minishell	*current;
// 	int			i;

// 	begin = set_mem_lst();
// 	if (!begin)
// 		return (NULL);
// 	i = 0;
// 	while (tokens && tokens[i])
// 	{
// 		current = set_mem_lst();
// 		if (!current)
// 			return (NULL);
// 		if(!ft_strncmp(tokens[i],"<<\0",3))
// 			current->type = APPEND;
// 		else if(!ft_strncmp(tokens[i],">>\0",3))
// 			current->type = HEREDOC;
// 		else if(!ft_strncmp(tokens[i],"<\0",2))
// 			current->type = INFILE;
// 		else if(!ft_strncmp(tokens[i],">\0",2))
// 			current->type = OUTFILE;
// 		if(current->type && tokens[i + 1])
// 		{
// 			current->value->name = tokens[i + 1];
// 			// wird das noch benötigt?
// 			current->value->exec = TRUE;

// 			i++;
// 		}
// 		if(!ft_strncmp(tokens[i],"|\0",2))
// 			current->type = PIPE;
// 		if(current->type)
// 				current->value->error = FALSE;
// 		ft_msh_add_back(&begin, current);
// 		i++;
// 	}
// 	ft_printf("\n");
// 	return (begin);
// }

int	spezial_char(char c)
{
	if(c == '<' || c == '>')
		return(1);
	return(0);
}

char	*ft_charjoin(char *s1, char c)
{
	char	*join;
	size_t	len;

	len = ft_strlen(s1) + 1;
	join = (char *)malloc(sizeof(char) * len + 1);
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, ft_strlen(s1) + 1);
	ft_strlcpy(&join[ft_strlen(s1)], &c, 1 + 1);
	return (join);
}

char	*prepare_line(char *line)
{
	ft_printf("%s\n",line);
	int	quotes_closed;
	int	i;
	char	*new_line;
	char	*old_line;
	char	*temp_line;

	quotes_closed = TRUE;
	i = 0;
	new_line = NULL;
	old_line = NULL;
	temp_line = NULL;
	while(line[i])
	{
		// temp_line = new_line;
		if(line[i] == ' ')
		{
			new_line = ft_charjoin(old_line,line[i]);
			ft_printf("%s\n",new_line);
			while(line[i] == ' ')
				i++;
		}
		i++;
	}
	return (new_line);
}

int	run_andi_main(int argc, char **argv)
{
	printf("%i,  %s\n",argc, argv[0]);
	char *line;
	char *new_line;

	line = NULL;
	while(1)
	{
		line = readline("minishell:");
		if(line)
			break;
	}
	new_line = prepare_line(line);
	ft_printf("%s\n",new_line);

				// char **tokens = ft_split(line, ' ');
				// if(!tokens)
				// {
				// 	printf("ARG IS EMPTY\n");
				// }
				// print_2d_arr(tokens);

				// t_minishell *msh;
				// msh = fill_lst(tokens);
				// printf_list(msh);

	// free_lst(msh);
	// free_2d_arr(tokens);
	// if(line)
	// 	free(line);

	return(0);
}
