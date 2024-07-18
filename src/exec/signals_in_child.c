/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_in_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:29:08 by psanger           #+#    #+#             */
/*   Updated: 2024/05/24 19:59:13 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	signal_c_heredoc(int signum)
{
	(void)signum;
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		ioctl(0, TIOCSTI, "\4");
	}
}

void	signal_c_handler(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(2, "\n", 2);
	rl_redisplay();
}

void	signal_c_in_child(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	write(2, "\n", 1);
	rl_redisplay();
}

void	signal_quit_handler(int signum)
{
	(void)signum;
	write(2, "Quit: ", 7);
	ft_putnbr_fd(signum, 2);
	write(2, "\n", 2);
}
