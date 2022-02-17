#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

char	*ft_realloc(char *s1)
{
	char	*s2;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	if (!i)
		return (NULL);
	s2 = malloc(i + 1);
	i = -1;
	while (s1[++i])
		s2[i] = s1[i];
	free(s1);
	s2[i] = 0;
	return (s2);
}

char	*get_next_line(int fd)
{
	int		i;
	char	*str;
	char	*c;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	str = malloc(BUFFER_SIZE + 1);
	i = 0;
	read(fd, c, 1);
	while (i <= BUFFER_SIZE)
	{
		str[i] = c[0];
		i++;
		if (c[0] == 10)
			break ;
		read(fd, c, 1);
	}
	str[i] = 0;
	str = ft_realloc(str);
	return (str);
}

int main(int ac, char **av)
{
	int	fd;
	int	i;

	if (ac != 2)
		return (1);
	fd = open(av[1], O_RDONLY);
	i = 0;
	while (i < 55)
	{
		printf("%s", get_next_line(fd));
		i++;
	}
	close(fd);
	return (0);
}
