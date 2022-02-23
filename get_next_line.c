/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:41:01 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/23 15:48:10 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*freejoin(char *s1, char *s2)
{
	char	*tmp;

	tmp = s1;
	s1 = ft_strjoin(s1, s2);
	free(tmp);
	tmp = NULL;
	return (s1);
}

static char	*find_end(char *line)
{
	int		i;
	char	*s;

	s = NULL;
	i = 0;
	while (line[i] && line[i] != 10)
		i++;
	if (!line[i])
		return (s);
	if (line[i + 1])
		s = ft_substr(line, i + 1, ft_strlen(line) - (i + 1));
	line[i + 1] = 0;
	return (s);
}

static char	*find_line(int fd, char *line, char *buffer)
{
	int		i;
	int		read_value;

	read_value = read(fd, buffer, BUFFER_SIZE);
	while (read_value != -1)
	{
		if (!read_value)
			return (line);
		buffer[read_value] = 0;
		if (!line)
			line = ft_strdup("");
		line = freejoin(line, buffer);
		i = 0;
		while (line[i] && line[i] != 10)
			i++;
		if (line[i] == 10)
			return (line);
		read_value = read(fd, buffer, BUFFER_SIZE);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	char		*buffer;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = malloc(sizeof(*buffer) * (BUFFER_SIZE + 1));
	line = find_line(fd, remainder, buffer);
	free(buffer);
	if (!line)
		return (NULL);
	remainder = find_end(line);
	return (line);
}
