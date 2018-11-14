#include "get_next_line.h"

static struct buffers	*new_buffer(int fd, struct buffers *buffers)
{
	int		a;
	struct buffers	*new;

	if (!(new = (struct buffers*)malloc(sizeof(*new))))
		return NULL;
	a = 0;
	buffers->next = new;
	new->fd = fd;
	new->next = NULL;
	new->previous = buffers;
	new->rest_index = 0;
	if (!(new->buf = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return NULL;
	while (a < BUFF_SIZE)
	{
		new->buf[a] = 1;
		a++;
	}
	return new;
}

static int	check_return(struct buffers *t, char **line, int a, int rest)
{
	int		b;

	b = strlen(*line);
	if (rest)
	{
		if (a < BUFF_SIZE)
			t->rest_index = a;
		else
			t->rest_index = 0;
	}
	if (((*line)[b - 2] == '\n' || (*line)[b - 2] == -1) && !(t->buf[a]))
		return 0;
	if (t->buf[a] == '\n' || t->buf[a] == -1)
		return 1;
	return 2;
}

static int	fill_n_append(struct buffers *t, char **line, int count)
{
	int	a = 0;
	char	tmp;
	char	*str;

	if (count < 0)
		return -1;
	t->buf[count] = 0;
	while (t->buf[a] && t->buf[a] != '\n' && 
		t->buf[a] != -1 && a < BUFF_SIZE)
		a++;
	if (count == 0 && (*line)[0] == 0)
		return 0;
	else if (count == 0)
		return 1;
	if (t->buf[a] == '\n' || t->buf[a] == -1)
		t->rest_index = a;
	tmp = t->buf[a];
	t->buf[a] = 0;
	if (!(str = strjoin(*line, t->buf)))
		return -1;
	t->buf[a] = tmp;
	free(*line);
	*line = str;
	return check_return(t, line, a, 0);
}

static int	check_fd(struct buffers *t, int fd, char **line)
{
	int	a;
	int	b = 0;

	t->fd = -1;
	while (t->next && t->fd != fd)
		t = t->next;
	if (!(t->next) && t->fd != fd)
		t = new_buffer(fd, t);
	if (!(t))
		return -1;
	if (!(*line = strnew(sizeof(char) * (BUFF_SIZE + 1))))
		return -1;
	b = 0;
	ft_bzero(*line, BUFF_SIZE + 1);
	if (t->buf[t->rest_index] == 0)
		return 0;
	a = t->rest_index;
	if (t->buf[a] != '\n' && t->buf[a] != -1 && a == 0)
		return 2;
	if (t->buf[a] == '\n' || t->buf[a] == -1)
		a++;
	while (a < BUFF_SIZE && t->buf[a] != '\n' &&
		t->buf[a] != -1 && t->buf[a])
		(*line)[b++] = t->buf[a++];
	(*line)[b] = 0;
	return check_return(t, line, a, 1);
}

int					get_next_line(const int fd, char **line)
{
	int			count;
	static struct buffers	buffers;
	struct buffers		*t;
	int			a;

	if (fd < 0 || !(line))
		return -1;
	t = &buffers;
	a = check_fd(t, fd, line);
	while (t->fd != fd)
		t = t->next;
	while (a == 2)
	{
		count = read(fd, t->buf, BUFF_SIZE);
		a = fill_n_append(t, line, count);
	}
	if (a == 0 || a == -1)
	{
		t->previous->next = t->next;
		if (t->next)
			t->next->previous = t->previous;
		free(t->buf);
		free(t);
	}
	return a;
}
