#include "fdf.h"

void		put_pixel(char **image, int current, int line, char *color)
{
	double		sizeline;

	sizeline = 3 * WINLEN;
	if (current >= sizeline * line && current <= sizeline * line + 1)
	{
		(*image)[current] = color[0];
		current++;
		(*image)[current] = color[0];
		current++;
		(*image)[current] = color[0];
	}
}

static double	conversion(char *str)
{
	double		b;

	b = 0;
	if (str[0] >= '0' && str[0] <= '9')
		b += (double)str[0] - 48;
	else if (str[0] >= 'A' && str[0] <= 'F')
		b += (double)str[0] - 55;
	else
		return (-1);
	if (str[1] >= '0' && str[1] <= '9')
		b += (double)(str[0] - 48) * 16;
	else if (str[1] >= 'A' && str[1] <= 'F')
		b += (double)(str[0] - 55) * 16;
	else
		return (-1);
	return (b);


static double	transmute(char *str, t_colors *element)
{
	double		a;
	double		b;

	a = 0;
	b = 0;
	if (!(element->color = (char *)malloc(sizeof(char) * 3)))
		return (0);
	while (a < 6)
	{
		element->color[b] = conversion(&str[a]);
		a += 2;
		b++;
	}
	printf("%s\n", element->color);
	return (1);
}

static double	initialize_color(t_colors *color, char **argv, int a;)
{
	if (!(color = (t_colors*)malloc(sizeof(t_colors))))
		return (0);
	if (!(transmute(argv[a])))
		return (0);
	return (1);
}

double			get_colors(int argc, char **argv, t_info *info)
{
	double			a;
	t_colors	*current;
	t_colors	*tmp;

	a = 2;
	if (a < argc)
	{
		if (!(initialize_color(info->colorlist, argv, a)))
			return (0);
		info->colorlist->next = NULL;
		a++;
	}
	tmp = info->colorlist;
	while (a < argc)
	{
		if (!(initialize_color(current, argv, a)))
			return (0);
		current->next = NULL;
		tmp->next = current;
		tmp = tmp->next;
		a++;
	}
	return (1);
}
