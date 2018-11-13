#include "fdf.h"

static double	*fill_tab(double *tab, char *str, double size)
{
	double		a = 0;
	double		b = 0;

	if (!(tab = (double*)malloc(sizeof(double) * size)))
		return (NULL);
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
	return (tab);
}

static double	*fill_empty(double *tab, double size)
{
	double	c = 0;

	if (!(tab = (double*)malloc(sizeof(double) * size)))
		return (NULL);
	while (c < size)
	{
		tab[c] = 0;
		c++;
	}
	return (tab);
}

double			create_tab(char *str, struct info *info, double size)
{
	double		a = 0;
	double		fd;
	char	*line;

	fd = open(str, O_RDONLY);
	if (!(info->tab = (double**)malloc(sizeof(double*) * size)))
		return (0);
	while (a < size)
	{
		if (get_next_line(fd, &line))
		{
			if (!(info->tab[a] = fill_tab(info->tab[a], line, size)))
				return (0);
			free(line);
		}
		else
		{
			if (!(info->tab[a] = fill_empty(info->tab[a], size)))
				return (0);
		}
		a++;
	}
	close(fd);
	return (1);
}

static double	get_linesize(char *line)
{
	double		a = 0;
	double		b = 0;

	while (line[a])
	{
		if (line[a] && isdigit(line[a]))
			b++;
		while (line[a] && isdigit(line[a]))
			a++;
		if (line[a] == ' ')
			a++;
		else if (!(line[a]))
			return (b);
		else
			return (0);
	}
	return (b);
}

double			init_get_size(char *str)
{
	double		ysize = 0;
	double		size = 0;
	double		fd;
	double		tmp = 0;
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
		return (ysize);
	return (size);
}
