/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:01:32 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/28 15:18:05 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/* frees the memory for the structure once the string
 * is empty. The list is then removed from the chain and
 * the previous list is linked to the next. */

static void	free_line(t_line **remainder, int fd)
{
	t_line	*current;
	t_line	*tmp;

	if (!*remainder)
		return ;
	current = *remainder;
	if (current->fd == fd)
	{
		*remainder = current->next;
		free(current);
		return ;
	}
	while (current->next && current->next->fd != fd)
		current = current->next;
	if (!current->next)
		return ;
	if (current->next->fd == fd)
	{
		tmp = current->next->next;
		free(current->next);
		current->next = tmp;
	}
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
	char	*tmp;

	read_value = read(fd, buffer, BUFFER_SIZE);
	while (read_value != -1)
	{
		if (!read_value)
			return (line);
		buffer[read_value] = 0;
		if (!line)
			line = ft_strdup("");
		tmp = line;
		line = ft_strjoin(line, buffer);
		free(tmp);
		tmp = NULL;
		i = 0;
		while (line[i] && line[i] != 10)
			i++;
		if (line[i] == 10)
			return (line);
		read_value = read(fd, buffer, BUFFER_SIZE);
	}
	return (NULL);
}

/* checks through each list element of the structure
 * to see if the current fd has been used. If it has not,
 * creates a new list element and adds it to the end of the
 * chain. */

static t_line	*find_fd(t_line **remainder, int fd)
{
	t_line	*current;
	t_line	*new;

	if (*remainder)
	{
		current = *remainder;
		while (current->fd != fd && current->next)
			current = current->next;
		if (current->fd == fd)
			return (current);
	}
	new = new_t_line();
	new->fd = fd;
	if (!(*remainder))
		*remainder = new;
	else
		current->next = new;
	return (new);
}

/* prints a new line using the file descriptor.
 * A static structure is used to keep track of
 * previously called file descriptors and their
 * respective leftover data. */

char	*get_next_line(int fd)
{
	static t_line	*remainder;
	t_line			*line;
	char			*current;
	char			*buffer;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	line = find_fd(&remainder, fd);
	buffer = malloc(sizeof(*buffer) * (BUFFER_SIZE + 1));
	current = find_line(fd, line->str, buffer);
	free(buffer);
	if (!current)
	{
		free_line(&remainder, fd);
		return (NULL);
	}
	line->str = find_end(current);
	return (current);
}
