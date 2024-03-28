/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:33:29 by ajehle            #+#    #+#             */
/*   Updated: 2024/03/28 10:11:13 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../include/minishell.h"

void	check_leaks(void)
{
	system("leaks minishell");
}

int	main(void)
{
	atexit(check_leaks);
	run_andi_main();
	return (0);
}
