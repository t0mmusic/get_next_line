/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:41:01 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/28 15:18:09 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* frees and reallocates a string while
 * joining it to another string. */

static char	*freejoin(char *s1, char *s2)
{
	char	*tmp;

	tmp = s1;
	s1 = ft_strjoin(s1, s2);
	free(tmp);
	tmp = NULL;
	return (s1);
}

/* searches through string to find newline
 * character or end of file. Null terminates
 * the string at that point, then returns any
 * leftovers for next function call. */

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

/* reads number of bytes determined by BUFFER_SIZE
 * and stores them in a buffer string. It then checks
 * to see if a new line or the end of file are found in the
 * static string. If they are not, the buffer is appended
 * to the string and the read function is called again. */

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

/* returns one line from a source determined by the fd.
 * if the fd is not valid, returns nothing. Since this
 * function uses a buffer of indeterminate size to take 
 * information in chunks, any leftover data must be stored
 * in the static char "remainder". */

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
