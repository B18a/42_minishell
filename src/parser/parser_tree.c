/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:31:55 by ajehle            #+#    #+#             */
/*   Updated: 2024/04/26 14:42:59 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


t_msh	*create_new(int type, char *content)
{
	t_msh	*new;

	new = NULL;
	new = (t_msh *)malloc(sizeof(t_msh));
	if (!new)
	{
		printf("Allocation create_new failed\n");
		return (NULL);
	}
	new->type = type;
	if (content)
	{
		new->cmd_args = ft_split(content, ' ');
		if (type == CMD && new->cmd_args)
			new->cmd_path = get_path(new->cmd_args[0]);
	}
	else
		new->cmd_path = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

char	*combine_cmd(char *old, char *add)
{
	char	*new;

	new = NULL;
	new = ft_str_cmd_join(old, add);
	printf("temp is %s\n", new);
	free(old);
	return(new);
}

t_msh	*make_branch(t_tok **tok)
{
	t_msh	*branch;
	char	*temp;
	char	*temp_old;

	branch = NULL;
	temp = NULL;
	temp_old = NULL;
	if (tok && *tok)
	{
		printf("TYPE IS %s\n", return_true_type((*tok)->type));
		if (is_redirect((*tok)->type))
		{
			if ((*tok)->next && (*tok)->next->type != PIPE && !is_redirect((*tok)->next->type))
			{
				branch = create_new((*tok)->type, (*tok)->next->content);
				*tok = (*tok)->next->next;
			}
			else
				return (printf("Synatx error\n"), NULL);
		}
		else if ((*tok)->type == BUILTIN)
		{
			branch = create_new((*tok)->type, (*tok)->content);
			*tok = (*tok)->next;
		}
		else if ((*tok)->type == CMD)
		{
			temp = ft_strdup((*tok)->content);
			*tok = (*tok)->next;
			while((*tok) && (*tok)->type == CMD)
			{
				temp = combine_cmd(temp, ((*tok)->content));
				*tok = (*tok)->next;
			}
			branch = create_new(CMD, temp);
			print_2d_arr(branch->cmd_args);
		}
	}
	if (branch == NULL)
		printf("make branch - failed\n");
	return (branch);
}