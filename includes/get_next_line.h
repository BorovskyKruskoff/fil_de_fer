#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 9999

# include <unistd.h>
# include <stdlib.h>

typedef struct			s_buffers
{
	char				*buf;
	int					rest_index;
	int					fd;
	struct s_buffers	*next;
	struct s_buffers	*previous;
}						t_buffers;

int						get_next_line(const int fd, char **line);

#endif
