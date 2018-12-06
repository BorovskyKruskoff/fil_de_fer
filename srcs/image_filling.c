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
	{
		printf("Right : %d\n", info->tab[a][b + 1] - info->tab[a][b]);
		return (double)(info->tab[a][b + 1] - info->tab[a][b]);
	}
	else
	{
		printf("Down : %d\n", info->tab[a + 1][b] - info->tab[a][b]);
		return (double)(info->tab[a + 1][b] - info->tab[a][b]);
	}
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
//	printf("Drawing a line at X = %d Y = %d\n\n"
//		, actual->current - (actual->line * WINLEN * 3), actual->line);
	info->angle.x = info->vectors_hor.x + dif(info, 0) *
		(float)info->height * sin(info->rot_x) * cos(info->rot_z);
	info->angle.y = info->vectors_hor.y + dif(info, 0) *
		(float)info->height * sin(info->rot_y) * cos(info->rot_z);
//	printf("X = %lf Y = %lf\n", info->vectors_hor.x + dif(info, 0) * (float)info->height * sin(info->rot_x), info->vectors_hor.y + dif(info, 0) * (float)info->height * sin(info->rot_y));
	if (!(trace(info)))
		return 0;
	return 1;
}

static int		get_column(struct point *actual, struct info *info)
{
	struct point	save;

	save.current = actual->current;
	save.line = actual->line;
//	printf("Drawing a column at X = %d Y = %d\n\n"
//		, actual->current - (actual->line * WINLEN * 3), actual->line);
	info->angle.x = info->vectors_vert.x + dif(info, 1) *
		(float)info->height * sin(info->rot_x) * cos(info->rot_z);
	info->angle.y = info->vectors_vert.y + dif(info, 1) *
		(float)info->height * sin(info->rot_y) * cos(info->rot_z);
//	printf("X = %lf Y = %lf\n", info->angle.x = info->vectors_vert.x + dif(info, 1) * (float)info->height * sin(info->rot_x), info->angle.y = info->vectors_vert.y + dif(info, 1) * (float)info->height * sin(info->rot_y));
	if (!(trace(info)))
		return 0;
	if (!(info->transition))
	{
		info->actual.current = save.current;
		info->actual.line = save.line;
	}
	else
		info->transition = 0;
	return 1;
}

/*
** dir indicates the direction of the point difference
** 1 means down, 0 means right
*/

int			fill_image(struct info *info)
{
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
		info->transition = 1;
		info->actual.current = info->startpoint.current;
		info->actual.line = info->startpoint.line;
		if (!(get_column(&info->actual, info)))
			return 1;
		info->startpoint.current = info->actual.current;
		info->startpoint.line = info->actual.line;
		info->y += 1;
	}
	printf("btp is %d, sizeline is %d\n", info->btp, info->sizeline);
	return 0;
}
