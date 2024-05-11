/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:31:55 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/10 22:33:14 by ajehle           ###   ########.fr       */
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
		// ???
		return (NULL);
	}
	new->type = type;
	new->cmd_args = NULL;
	new->cmd_path = NULL;
	new->left = NULL;
	new->right = NULL;
	new->stdin_cpy = 0;
	new->stdout_cpy = 0;
	if (content)
	{
		// printf("TYPE BEVOR SPLIT |%s|\n",return_true_type(type));
		// printf("CONTENT BEVOR SPLIT |%s|\n",content);
		if(type == BUILTIN)
		{
			new->cmd_args = ft_split_first_word(content, ' ');
			// printf("AFTER SPLIT |%s|\n",new->cmd_args[1]);
		}
		else
		{
																// ????
													new->cmd_args = ft_split(content, ' ');
		// test 62 geht nur mit den unteren 3 zeilen
		// new->cmd_args = (char**)malloc(sizeof(char*) + 1);
		// new->cmd_args[0] = ft_strdup(content);
		// new->cmd_args[1] = NULL;

		}
		if (type == CMD && new->cmd_args)
			new->cmd_path = get_path(new->cmd_args[0]);
	}
	if (new->type == HEREDOC) {
		new->stdin_cpy = dup(STDIN_FILENO);
		new->stdout_cpy = dup(STDOUT_FILENO);
	}
	return (new);
}



t_msh	*make_branch(t_tok **tok)
{
	t_msh	*branch;
	char	*temp;

	branch = NULL;
	temp = NULL;
	if (tok && *tok)
	{
		if (is_redirect((*tok)->type))
		{
			if ((*tok)->next && (*tok)->next->type != PIPE
				&& !is_redirect((*tok)->next->type))
			{
				branch = create_new((*tok)->type, (*tok)->next->content);
				*tok = (*tok)->next->next;
			}
			else
				return (printf("Synatx error\n"), NULL);
		}
		else if ((*tok)->type == BUILTIN)
		{
			temp = ft_strdup_space((*tok)->content);
			// temp = ft_strdup((*tok)->content);
			*tok = (*tok)->next;
			// while ((*tok) && ((*tok)->type == CMD || (*tok)->type == BUILTIN))
			// printf("1TEMP is |%s|\n",temp);
			while ((*tok) && ((*tok)->type == CMD || (*tok)->type == BUILTIN || (*tok)->type == DQUOTE || (*tok)->type == QUOTE))
			{
				// printf("type is |%s|\n",(return_true_type((*tok)->type)));
				// printf("temp is |%s|\n",(*tok)->content);
				temp = combine_cmd(temp, ((*tok)->content), ((*tok)->type));
				// printf("2TEMP is |%s|\n",temp);
				*tok = (*tok)->next;
				temp = erase_space(temp);
			}
			branch = create_new(BUILTIN, temp);
			if (temp)
				free(temp);
		}
		// else if ((*tok)->type == CMD && !(ft_strncmp((*tok)->content,"",1) == 0)) //segfault bei "$EMPTY echo hi"
		// else if ((*tok)->type == CMD)
		else
		{
			{
				temp = ft_strdup((*tok)->content);
				*tok = (*tok)->next;
				while ((*tok) && (*tok)->type == CMD)
				{
					temp = combine_cmd(temp, ((*tok)->content) , ((*tok)->type));
					*tok = (*tok)->next;
				}
				branch = create_new(CMD, temp);
				if (temp)
					free(temp);
			}
		}
			// print_2d_arr(branch->cmd_args);
	}
	// if (branch == NULL)
	// 	printf("make branch - failed\n");
	return (branch);
}
