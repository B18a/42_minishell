/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:32:19 by psanger           #+#    #+#             */
/*   Updated: 2024/05/24 19:35:39 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	read_heredoc(t_env **env, t_msh *list, int *pfd, int exit_code)
{
	char	*buffer;
	char	*del;
	char	*temp;

	buffer = NULL;
	temp = list->cmd_args[0];
	del = ft_strjoin(temp, "\n");
	write(1, "> ", 2);
	buffer = get_next_line(0);
	if (buffer == NULL)
		return (write(1, "\n", 2));
	buffer = ft_expand(buffer, env, DQUOTE, exit_code);
	while (ft_strncmp(buffer, del, ft_strlen(del) + 1) != 0)
	{
		write(1, "> ", 2);
		ft_putstr_fd(buffer, pfd[1]);
		free(buffer);
		buffer = get_next_line(0);
		if (buffer == NULL)
			return (write(1, "\n", 2));
		buffer = ft_expand(buffer, env, DQUOTE, 0);
	}
	if (buffer != NULL)
		free(buffer);
	return (0);
}

int	heredoc(t_msh *list, t_env **env, int exit_code)
{
	int		pfd[2];

	signal(SIGINT, signal_c_heredoc);
	if (list == NULL)
	{
		write(2, "ERROR LIST\n", 12);
		exit(1);
	}
	if (pipe(pfd) < 0)
	{
		write(2, "ERROR PIPE HEREDOC\n", 20);
		exit(1);
	}
	read_heredoc(env, list, pfd, exit_code);
	list->pipe_heredoc[0] = pfd[0];
	close (pfd[1]);
	signal(SIGINT, signal_c_handler);
	return (0);
}

void	handle_heredoc(t_env **env, t_msh *root, int exit_code)
{
	if (!root)
		return ;
	if (root->type == HEREDOC)
		heredoc(root, env, exit_code);
	handle_heredoc(env, root->left, exit_code);
	handle_heredoc(env, root->right, exit_code);
}
