#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.c"
#include "get_next_line_utils.c"

int main(int ac, char **av)
{
	int	fd;
	int	i;

	if (ac != 2)
		return (1);
	fd = open(av[1], O_RDONLY);
//	printf("%zi\n", read(fd, "", 1));
	i = 0;
	while (i < 10)
	{
		printf("%s", get_next_line(fd));
		i++;
	}
	close(fd);
	return (0);
}