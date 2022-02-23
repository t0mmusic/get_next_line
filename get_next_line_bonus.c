/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:01:32 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/23 15:06:13 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

t_line	*find_fd(t_line **remainder, int fd)
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

char	*get_next_line(int fd)
{
	static t_line	*remainder;
	t_line			*line;
	char			*current;
	char			*buffer;
	int				read_value;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	line = find_fd(&remainder, fd);
	buffer = malloc(sizeof(*buffer) * (BUFFER_SIZE + 1));
	current = find_line(fd, line->str, buffer);
	free(buffer);
	if (!current)
		return (NULL);
	line->str = find_end(current);
	return (current);
}
