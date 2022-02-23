#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line_bonus.h"
#include "get_next_line_bonus.c"
#include "get_next_line_utils_bonus.c"

int main(int ac, char **av)
{
	int		fd;
	int		fd1;
	int		i;
	char	*str;

	fd = open(av[1], O_RDONLY);
	fd1 = open(av[2], O_RDONLY);
	str = get_next_line(fd);
	i = 0;
	while (str)
	{
		printf("%s", str);
		str = get_next_line(fd1);
		printf("%s", str);
		str = get_next_line(fd);
		i++;
	}
	close(fd);
	return (0);
}