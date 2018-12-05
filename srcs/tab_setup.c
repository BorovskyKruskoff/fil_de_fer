#include "fdf.h"

static int *fill_tab(int *tab, char *str, int size)
{
	int		a = 0;
	int		b = 0;

	if (!(tab = (int*)malloc(sizeof(int) * size)))
		return NULL;
	while (a < size)
	{
		tab[a++] = atoi(&str[b]);
		while (str[b] && str[b] != ' ' && str[b] != '\n')
			b++;
		if (str[b] == ' ')
			b++;
		else if (!(str[b]) || str[b] == '\n')
		{
			while (a < size)
				tab[a++] = 0;
		}
	}
	return tab;
}

static int *create_empty(int *tab, int size)
{
	int	c = 0;

	if (!(tab = (int*)malloc(sizeof(int) * size)))
		return NULL;
	while (c < size)
	{
		tab[c] = 0;
		c++;
	}
	return tab;
}

int create_tab(char *str, struct info *info, int size)
{
	int		a = 0;
	int		fd;
	char	*line;

	fd = open(str, O_RDONLY);
	if (!(info->tab = (int**)malloc(sizeof(int*) * size)))
		return 0;
	while (a < size)
	{
		if (get_next_line(fd, &line))
		{
			if (!(info->tab[a] = fill_tab(info->tab[a],
				line, size)))
				return 0;
			free(line);
		}
		else
		{
			if (!(info->tab[a] = create_empty(info->tab[a],
				size)))
				return 0;
		}
		a++;
	}
	close(fd);
	return 1;
}

static int get_linesize(char *line)
{
	int		a = 0;
	int		b = 0;

	while (line[a])
	{
		if (line[a] && isdigit(line[a]))
			b++;
		while (line[a] && isdigit(line[a]))
			a++;
		if (line[a] == ' ')
			a++;
		else if (!(line[a]))
			return b;
		else
			return 0;
	}
	return b;
}

int init_get_size(char *str)
{
	int		ysize = 0;
	int		size = 0;
	int		fd;
	int		tmp = 0;
	char	*line;

	fd = open(str, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		tmp = get_linesize(line);
		if (tmp <= 0)
			return (0);
		if (size < tmp)
			size = tmp;
		free(line);
		ysize++;
	}
	close(fd);
	if (ysize > size)
		return ysize;
	return size;
}
