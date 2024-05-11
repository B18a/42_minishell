/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 23:47:19 by psanger           #+#    #+#             */
/*   Updated: 2024/05/10 10:59:25 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env_free(t_env *env)
{
	t_env	*curr;
	t_env	*prev;

	if (env == NULL)
		return ;
	prev = NULL;
	curr = env;
	while (curr != NULL)
	{
		if (prev != NULL)
		{
			free(prev->value);
			free(prev->key);
			free(prev);
		}
		prev = curr;
		curr = curr->next;
	}
	free(prev->value);
	free(prev->key);
	free(prev);
}

void	env_lstadd_front(t_env **lst, t_env *new)
{
	if (new == NULL)
		return ;
	else
	{
		new->next = lst[0];
		lst[0] = new;
	}
}

t_env	*env_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	if (!(lst->next))
		return (lst);
	else
		return (env_lstlast(lst->next));
}

void	env_lstadd_back(t_env **lst, t_env *new)
{
	if (!*lst)
		env_lstadd_front(lst, new);
	else
		env_lstlast(*lst)->next = new;
}
