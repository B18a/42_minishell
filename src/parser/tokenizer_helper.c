/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:46:24 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/17 15:08:22 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_tok	*ft_tok_new(char *content, int type)
{
	t_tok	*new;

	new = (t_tok *)malloc(sizeof(t_tok));
	if (!new)
		return (NULL);
	// new->content = content;
	new->content = ft_strdup(content);
	new->type = type;
	new->syntax_error = FALSE;
	new->next = NULL;
	return (new);
}

t_tok	*ft_tok_last(t_tok *lst)
{
	if (!lst) {
		return (NULL);
	}
	if (!(lst->next)) {
		return (lst);
	}
	else {
		return (ft_tok_last(lst->next));
	}
}

void	ft_tok_add_front(t_tok **lst, t_tok *new)
{
	if (new == NULL)
		return ;
	else
	{
		new->next = lst[0];
		lst[0] = new;
	}
}

void	ft_tok_add_back(t_tok **lst, t_tok *new)
{
	if (!*lst) {
		ft_tok_add_front(lst, new);
	}
	else {
		ft_tok_last(*lst)->next = new;
	}
}
