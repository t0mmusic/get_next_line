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
	char	*fd_array;
	int		i;
	char	*str;

	fd_array = malloc(sizeof(*fd_array) * (ac + 1));
	i = 0;
	while (++i <= ac)
		fd_array[i - 1] = open(av[i], O_RDONLY);
	fd_array[i] = 0;
	str = get_next_line(fd_array[0]);
	i = 1;
	while (str)
	{
		printf("%s", str);
		if (str && i == ac - 1)
			i = 0;
		str = get_next_line(fd_array[i]);
		if (!str)
			i = 0;
		while (!str && i < ac && fd_array[i + 1])
		{
			i++;
			str = get_next_line(fd_array[i]);
		}
		i++;
	}
	close(fd);
	return (0);
}
