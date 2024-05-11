/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tree_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:31:55 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/10 22:11:58 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


char	**ft_split_first_word(char	*str, char c)
{
	char	**word = NULL;
	int	i = 0;
	int	j = 0;
	word = (char**)malloc(sizeof(char*) * (2 + 1));
	if(!word)
		return(NULL);
	while(str && str[i] != c)
		i++;
	word[0] = ft_substr(str,0,i);
	j = i;
	while(str && str[j])
		j++;
	word[1] = ft_substr(str,i+1,(j-i));
	word[2] = NULL;
	return(word);
}

char *ft_join_without_space(char const *s1, char const *s2)
{
	char	*join;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	// printf("s1 %s	|	s2 %s\n", s1, s2);
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!join)
		return (NULL);
	// printf("s11 %s	|	s22 %s\n", s1, s2);
	if (len1)
	{
		ft_strlcpy(join, s1, len1 + 1);
	}
	if (len2)
		ft_strlcpy(&join[len1], s2, len2 + 1);
	// printf("JOINED STRING |%s|\n", join);
	return (join);
}


char	*combine_cmd(char *old, char *add, int type)
{
	static int space = 1;
	char	*new;

	new = NULL;
	// printf("SPACE0 |%i|\n",space);
	// if(add == NULL)
	// 	printf("add is null\n");
	// 											printf("stringcmp |%i|\n",ft_strncmp(add,"",1));
	// 											// printf("add |%s|\n",add);
	// 											printf("TYPE |%s|\n",return_true_type(type));
	// if(ft_strncmp(add,"",1))
	if(((type == QUOTE || type == DQUOTE) && ft_strncmp(add,"",1) == 0))
	{
		// return(old);
		space = 0;
	}
	if(type == QUOTE)
	{
		// return(old);
		space = 0;
	}

	// if(ft_strncmp(add,"",1) && type != QUOTE && type != DQUOTE && space)
													// printf("SPACE |%i|\n",space);
	// if(type != QUOTE && type != DQUOTE && space)
	if(space)
	{
		// printf("WITH\n");
		// printf("ADD |%s|\n",add);
		// printf("OLD |%s|\n",old);
		// printf("NEW |%s|\n",new);

		new = ft_join_with_space(old, add);
		// printf("NEW NEW |%s|\n",new);
	}
	else
	{

		// printf("WITHOUT\n");
		new = ft_join_without_space(old, add);

	}
	free(old);
	return (new);
}
char	*ft_strdup_space(const char *s1)
{
	size_t	len;
	char	*ptr;

	len = ft_strlen(s1);
	ptr = (char *)malloc(sizeof(char) * len + 2);
	if (!ptr)
		return (NULL);
	ft_strlcpy (ptr, s1, len + 1);
	ptr[len ] = ' ';
	ptr[len + 1] = '\0';
	// printf("PTR|%zu|\n",len);
	// printf("PTR|%c|\n",' ');
	// printf("PTR|%s|\n",ptr);
	return (ptr);
}


char *erase_space(char *str)
{
	int i = 0;
	char *new;

	while(str && str[i])
	{
		if((str[i] == ' ' && str[i+1] && str[i + 1] == ' '))
		{
			new = ft_strdup(str);
			while(str[i + 1])
			{
				new[i] = str[i + 1];
				i++;
			}
			new[i] = '\0';
			free(str);
			// printf("NEW |%s|\n", new);
			return(new);
		}
		i++;
	}
	return(str);
}
