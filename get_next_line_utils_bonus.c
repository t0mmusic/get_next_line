/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:08:36 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/28 15:25:38 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/* Returns a string that is a fragment of the input string. */

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*sub;
	size_t		remainder;
	size_t		i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		remainder = 0;
	else
		remainder = ft_strlen(s) - start;
	if (remainder < len)
		len = remainder;
	sub = malloc(sizeof(*sub) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (s[i] && i < len)
	{
		sub[i] = s[i + start];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

/* Finds the length of a null terminated array. */

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/* duplicates a string and returns a copy
 * assigned to heap memory. */

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;

	s2 = malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

/* returns a string that is a duplicate of the second
 * input string appended to the first. */

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*r;

	if (!s1 || !s2)
		return (NULL);
	r = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!r)
		return (NULL);
	i = -1;
	while (s1[++i])
		r[i] = s1[i];
	j = 0;
	while (s2[j])
		r[i++] = s2[j++];
	r[i] = '\0';
	return (r);
}

/* Initialises a new t_line structure. This will keep
 * track of the file desciptor, the remainder of the 
 * string buffer, and the next element in the list. */

t_line	*new_t_line(void)
{
	t_line	*new;

	new = malloc(sizeof(*new));
	new->fd = 0;
	new->next = NULL;
	new->str = NULL;
	return (new);
}
