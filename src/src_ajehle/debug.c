/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:36:44 by ajehle            #+#    #+#             */
/*   Updated: 2024/04/04 11:50:06 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_2d_arr(char **arr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (arr)
	{
		while (arr[i])
		{
			ft_printf("				[%i]	", i);
			while (arr[i][j])
			{
				ft_printf("%c", arr[i][j]);
				j++;
			}
			ft_printf("\n");
			j = 0;
			i++;
		}
	}
	else
		ft_printf("(null)\n");
}

char	*return_true_type(int type)
{
	if(type == PIPE)
		return("PIPE");
	if(type == PIPE_WRITE)
		return("PIPE_WRITE");
	if(type == PIPE_READ)
		return("PIPE_READ");
	if(type == CMD)
		return("CMD");
	if(type == INFILE)
		return("INFILE");
	if(type == OUTFILE)
		return("OUTFILE");
	if(type == APPEND)
		return("APPEND");
	if(type == HEREDOC)
		return("HEREDOC");
	if(type == BUILDIN)
		return("BUILDIN");
	return("WRONG TYPE!!!");
}

void	printf_list(t_minishell *lst)
{
	while (lst)
	{
		ft_printf("TYPE	:	%s\n",return_true_type(lst->type));
		ft_printf("VALUES	:\n");
		ft_printf("		BUILDIN:	%s\n",lst->value->buildin);
		ft_printf("		CMD:		%s\n",lst->value->cmd);
		ft_printf("		CMD_ARGS:		\n");
				print_2d_arr(lst->value->cmd_args);
		ft_printf("		NAME:		%s\n",lst->value->name);
		ft_printf("		EXEC:		%i\n",lst->value->exec);
		ft_printf("-------------------------------------------\n");
		ft_printf("\n");
		lst = lst->next;
	}
}
