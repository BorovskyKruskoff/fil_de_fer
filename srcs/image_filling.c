#include "fdf.h"

/*
** dir indicates the direction of the point difference
** 1 means down, 0 means right
*/

double			dif(struct info *info, double dir)
{
	int	a = info->y;
	int	b = info->x;
	if (dir == 0)
		return (double)(info->tab[a][b] - info->tab[a][b + 1]);
	else
		return (double)(info->tab[a][b] - info->tab[a + 1][b]);
}

//sqrt and pow are functions that exist

double			get_angle(struct info *info, double dir)
{
	double	itself;
	double	result;
	double	magnitude;

	itself = dif(info, dir) / info->height;
	magnitude = sqrt((1 + (itself * itself)));
	result = acos(1.00 / magnitude);
	if (itself < 0)
		return -result;
	return result;
}

static int		get_line(struct point *actual, struct info *info)
{
	info->angle.x = (info->vectors_hor.x + dif(info, 0) *
		(float)info->height * sin(info->rot_x)) * info->gap;
	info->angle.y = (info->vectors_hor.y + dif(info, 0) *
		(float)info->height * sin(info->rot_y)) * info->gap;
//	printf("LINE   X = %f,Y = %f\n", info->angle.x, info->angle.y);
	if (!(trace(info)))
		return 1;
	return 0;
}

static int		get_column(struct point *actual, struct info *info)
{
	info->angle.x = (info->vectors_vert.x + dif(info, 1) *
		(float)info->height * sin(info->rot_x)) * info->gap;
	info->angle.y = (info->vectors_vert.y + dif(info, 1) *
		(float)info->height * sin(info->rot_y)) * info->gap;
//	printf("COLUMN   X = %f,Y = %f\n", info->angle.x, info->angle.y);
	if (!(trace(info)))
		return 1;
	return 0;
}

/*
** dir indicates the direction of the point difference
** 1 means down, 0 means right
*/

int			fill_image(struct info *info)
{
	printf("\n\n%lf\n\n", info->gap);
	info->actual.current = info->startpoint.current;
	info->actual.line = info->startpoint.line;
	while (info->y + 1 < info->size - 1)
	{
		info->x = 0;
		while (info->x + 1 < info->size)
		{
			if (!(get_line(&info->actual, info)))
				return 1;
			if (!(get_column(&info->actual, info)))
				return 1;
			info->x += 1;
		}
		info->actual.current = info->startpoint.current;
		info->actual.line = info->startpoint.line;
		if (!(get_column(&info->actual, info)))
			return 1;
		info->startpoint.current = info->actual.current;
		info->startpoint.line = info->actual.line;
		info->y += 1;
	}
	return 0;
}
