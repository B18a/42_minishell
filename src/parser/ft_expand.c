/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 23:02:09 by psanger           #+#    #+#             */
/*   Updated: 2024/05/23 15:59:35 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_expand(char *argv, t_env **env, int type, int exit_code)
{
	char	*res;
	int		size;

	res = NULL;
	if (type == QUOTE)
		return (argv);
	size = get_res_len_expander(argv, env, exit_code);
	res = malloc(sizeof(char) * (size + 1));
	res = get_res_expander(argv, env, res, exit_code);
	free(argv);
	return (res);
}
