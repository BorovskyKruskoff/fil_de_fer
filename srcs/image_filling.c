#include "fdf.h"

/*
** dir indicates the direction of the point difference
** 1 means down, 0 means right
*/

double				dif(t_info *info, double dir)
{
	double		a;
	double		b;

	a = info->y;
	b = info->x;
	if (dir == 0)
		return (info->tab[a][b] - info->tab[a][b + 1]);
	else
		return (info->tab[a][b] - info->tab[a + 1][b]);
}

//sqrt and pow are functions that exist

double			get_angle(t_info *info, double dir)
{
	double	itself;
	double	result;
	double	magnitude;

	itself = dif(info, dir) / info->height;
	magnitude = sqrt((1 + (itself * itself)));
	result = acos(1.00 / magnitude);
	if (itself < 0)
		return (-result);
	return (result);
}

void			get_line(t_point *actual, t_info *info)
{
	info->angle->x = info->vectors_hor->x * (dif(info, 0) * info->height *
		cos(info->rot_x));
	info->angle->y = info->vectors_hor->y * (dif(info, 0) * info->height *
		cos(info->rot_y));
	trace(actual, info);
}

void			get_column(t_point *actual, t_info *info)
{
	double		currentsave;
	double		linesave;

	currentsave = actual->current;
	linesave = actual->line;
	info->angle->x = info->vectors_vert->x * (dif(info, 1) * info->height
		 * cos(info->rot_x));
	info->angle->y = info->vectors_vert->y * (dif(info, 1) * info->height
		 * cos(info->rot_y));
	trace(actual, info);
	if (!(info->transition == 1))
	{
		actual->current = currentsave;
		actual->line = linesave;
	}
	else
		info->transition = 0;
}

/*
** dir indicates the direction of the point difference
** 1 means down, 0 means right
*/

double			fill_image(char **image, t_info *info)
{
	t_point	*actual;

	actual->current = info->startpoint.current;
	actual->line = info->startpoint.line;
	while (info->y + 1 < info->size - 1)
	{
		info->x = 0;
		while (info->x + 1 < info->size)
		{
			get_line(actual, info);
			get_column(actual, info);
			info->x += 1;
		}
		info->transition = 1;
		get_column(algo->startpoint, info);
		actual->current = info->startpoint->current;
		actual->line = info->startpoint->line;
		info->y += 1;
	}
}
