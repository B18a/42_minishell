/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreasjehle <andreasjehle@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:33:29 by ajehle            #+#    #+#             */
/*   Updated: 2024/03/27 18:43:36 by andreasjehl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

void	check_leaks(void)
{
	system("leaks so_long");
}

int	main(int argc, char **argv)
{
	run_andi_main(argc, argv);
	return (0);
}
