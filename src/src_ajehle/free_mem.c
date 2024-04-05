/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:19:29 by ajehle            #+#    #+#             */
/*   Updated: 2024/04/05 11:13:44 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_2d_arr(char	**arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while(arr && arr[i])
		{
			// ft_printf("FREE ARR[%i]\n",i);
			free(arr[i]);
			i++;
		}
		// ft_printf("FREE ARR\n");
		free(arr);
	}
}


void	free_value(t_value *value)
{
	int	i;

	i = 0;
	if(value)
	{
		if(value->cmd_args)
		{
			while(value->cmd_args && value->cmd_args[i])
			{
				// ft_printf("FREE CMD ARGS[%i]\n",i);
				free(value->cmd_args[i]);
				i++;
			}
			// ft_printf("FREE CMD ARGS\n");
			free(value->cmd_args);
		}
		// ft_printf("FREE VALUE\n");
		free(value);

		/*	NOT NECESSARY ?
		if(value->buildin)
		{
			ft_printf("FREE BUILDIN\n");
			free(value->buildin);
		}
		if(value->cmd)
		{
			ft_printf("FREE CMD\n");
			free(value->cmd);
		}
		if(value->name)
		{
			ft_printf("FREE NAME\n");
			free(value->name);
		}
		*/
	}
}

void	free_lst(t_minishell *lst)
{
	if(lst && lst->next)
		free_lst(lst->next);
	if(lst)
	{
		if(lst->value)
			free_value(lst->value);
		// ft_printf("FREE LST\n");
		free(lst);
	}
}
