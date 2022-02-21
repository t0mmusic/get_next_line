/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:41:01 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/21 16:36:27 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*initial_check(int *close, int fd)
{
	char	*s1;

	s1 = malloc(sizeof(*s1) * BUFFER_SIZE + 1);
	if (!s1)
		return (NULL);
	*close = read(fd, s1, BUFFER_SIZE);
	s1[BUFFER_SIZE] = 0;
	return (s1);
}

char	*check_remainder(char *s1, int *close, int fd)
{
	char	*tmp;
	char	*s2;
	int		i;
	int		len;

	i = 0;
	while (s1[i] != 10 && s1[i])
		i++;
	if (s1[i] != 10 || !s1[i])
	{
		len = ft_strlen(s1);
		s2 = malloc(sizeof(*tmp) * BUFFER_SIZE);
		*close = read(fd, s2, BUFFER_SIZE);
		tmp = s1;
		s1 = ft_strjoin(s1, s2);
		if (!s1)
			return (NULL);
		free(tmp);
		free(s2);
		s1[len + BUFFER_SIZE] = 0;
	}
	return (s1);
}

char	*get_next_line(int fd)
{
	static char	*s1;
	char		*s2;
	int			i;
	int			len;
	int			read_value;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	if (s1)
		s1 = check_remainder(s1, &read_value, fd);
	else
		s1 = initial_check(&read_value, fd);
	if (!read_value)
		return (NULL);
	i = 0;
	while (s1[i] != 10 && s1[i])
		i++;
	if (s1[i] != 10)
		return (NULL);
	s2 = ft_substr(s1, 0, i + 1);
	len = ft_strlen(s1);
	s1 = ft_substr(s1, i + 1, len - (i + 1));
//	printf("{%s}", s2);
	return (s2);
}
