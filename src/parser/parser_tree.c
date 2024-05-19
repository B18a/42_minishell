/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:31:55 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/18 12:50:20 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_new_msh(t_msh *new)
{
	new->cmd_args = NULL;
	new->cmd_path = NULL;
	new->left = NULL;
	new->right = NULL;
	new->stdin_cpy = 0;
	new->stdout_cpy = 0;
	new->root = NULL;

}

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
	init_new_msh(new);
	new->type = type;
	if (content )
	{
		new->cmd_args = malloc(sizeof(char *) * 2);
		new->cmd_args[0] = ft_strdup(content);
		new->cmd_args[1] = NULL;
	 	if (type == CMD && new->cmd_args)
	 		new->cmd_path = get_path(new->cmd_args[0]);
	}
	if (new->type == HEREDOC || new->type == BUILTIN) {
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
	if (tok)
	{
			branch = create_new((*tok)->type, (*tok)->content);
													//	branch = (t_msh *)malloc(sizeof(t_msh));
													//	init_new(branch);
		// if (is_redirect((*tok)->type))
		// {
		// }
		// else if ((*tok)->type == BUILTIN)
		// {
		// 	branch = create_new(BUILTIN, (*tok)->content);
		// }
		// else if ((*tok)->type == CMD)
		// {
		// 	branch = create_new(CMD, (*tok)->content);
		// }
		(*tok) = (*tok)->next;
	}
	// if condition wird nicht benoetigt ,da return value geprueft wird
	// if (branch == NULL)
	// 	printf("make branch - failed\n");
	return (branch);
}
