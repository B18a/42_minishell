/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:39:46 by psanger           #+#    #+#             */
/*   Updated: 2024/04/10 16:31:23 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_line_ps(char *line)
{
	int		i;
	int		temp;
	char	*new_line;

	i = 0;
	temp = 0;
	if (line == NULL)
		return (NULL);
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		temp++;
	new_line = ft_substr(line, 0, (i + temp));
	if (new_line == NULL)
		return (NULL);
	if (new_line [0] == '\0')
	{
		free(new_line);
		new_line = NULL;
	}
	free (line);
	line = NULL;
	return (new_line);
}

char	*get_remainder(char *line)
{
	int		i;
	int		line_len;
	char	*new_remainder;

	i = 0;
	if (line == NULL)
		return (NULL);
	line_len = ft_strlen(line);
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (0);
	new_remainder = ft_substr(line, (i + 1), (line_len - i));
	if (new_remainder == NULL)
		return (NULL);
	if (new_remainder [0] == '\0')
	{
		free(new_remainder);
		new_remainder = NULL;
	}
	return (new_remainder);
}

char	*func(char *remainder, char *buffer)
{
	char	*new_remainder;

	new_remainder = ft_strjoin(remainder, buffer);
	if (new_remainder == NULL)
		return (NULL);
	free (remainder);
	remainder = NULL;
	return (new_remainder);
}

char	*get_buffer(char *remainder, char *buffer, int fd)
{
	int		charsread;

	charsread = 1;
	while (charsread != 0)
	{
		charsread = read(fd, buffer, BUFFER_SIZE);
		if (charsread < 0)
			return (NULL);
		if (charsread == 0)
			break ;
		buffer[charsread] = '\0';
		if (remainder == NULL)
			remainder = ft_strdup("");
		if (remainder == NULL)
			return (NULL);
		remainder = func(remainder, buffer);
		if (ft_strchr (buffer, '\n'))
			break ;
	}
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	line = get_buffer(remainder, buffer, fd);
	if (line == NULL)
	{
		free (remainder);
		remainder = NULL;
	}
	free (buffer);
	buffer = NULL;
	remainder = get_remainder(line);
	line = get_line_ps(line);
	return (line);
}
// int	main(void)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("test.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (1);
// 	line = get_next_line(fd);
// 	printf("line 1 |%s|\n", line);
// 	line = get_next_line(fd);
// 	printf("line 2 |%s|\n", line);
// 	line = get_next_line(fd);
// 	printf("line 3 |%s|\n", line);
// 	line = get_next_line(fd);
// 	printf("line 4 |%s|\n", line);
// 	close(fd);
// 	return (0);
// }
