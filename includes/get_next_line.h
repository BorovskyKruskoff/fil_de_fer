#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 9999

# include <strings.h>
# include <unistd.h>
# include <stdlib.h>

struct	buffers
{
	char		*buf;
	int		rest_index;
	int		fd;
	struct buffers	*next;
	struct buffers	*previous;
};

int	get_next_line(const int fd, char **line);

#endif
