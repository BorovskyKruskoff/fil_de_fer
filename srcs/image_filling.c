#include "fdf.h"

/*
** dir indicates the direction of the point difference
** 1 means down, 0 means right
*/

double dif(struct info *info, double dir)
{
	int	a = info->y;
	int	b = info->x;
	if (dir == 0)
	{
		return (double)(info->tab[a][b + 1] - info->tab[a][b]);
	}
	else
	{
		return (double)(info->tab[a + 1][b] - info->tab[a][b]);
	}
}

//sqrt and pow are functions that exist

double get_angle(struct info *info, double dir)
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

static void get_line(struct info *info)
{
	info->angle.x = info->vectors_hor.x + dif(info, 0)
		* (float)info->height * sin(info->rot_x) * cos(info->rot_z);
	info->angle.y = info->vectors_hor.y + dif(info, 0)
		* (float)info->height * sin(info->rot_y) * cos(info->rot_z);
	trace(info);
}

static void get_column(struct info *info)
{
	info->angle.x = info->vectors_vert.x + dif(info, 1)
		* (float)info->height * sin(info->rot_x) * cos(info->rot_z);
	info->angle.y = info->vectors_vert.y + dif(info, 1)
		* (float)info->height * sin(info->rot_y) * cos(info->rot_z);
	trace(info);
}

void swap_decimals(struct vectors decimals_1, struct vectors decimals_2)
{
	struct vectors storage;

	storage.x = decimals_1.x;
	storage.y = decimals_1.y;
	decimals_1.x = decimals_2.x;
	decimals_1.y = decimals_2.y;
	decimals_2.x = storage.x;
	decimals_2.y = storage.y;
}

void draw_lines(struct info *info)
{
	struct vectors decimal_storage;

	info->y = 0;
	while (info->y + 1 < info->size)
	{
		info->x = 0;
		decimal_storage.x = 0.0;
		decimal_storage.y = 0.0;
		get_column(info);
		info->y += 1;
		swap_decimals(info->decimals, decimal_storage);
		info->startpoint.current = info->actual.current;
		info->startpoint.line = info->actual.line;
		while (info->x + 1 < info->size)
		{
			get_line(info);
			info->x += 1;
		}
		swap_decimals(info->decimals, decimal_storage);
		info->actual.current = info->startpoint.current;
		info->actual.line = info->startpoint.line;
	}	
}

void draw_columns(struct info *info)
{
	struct vectors decimal_storage;

	info->x = 0;
	while (info->x + 1 < info->size)
	{
		info->y = 0;
		decimal_storage.x = 0.0;
		decimal_storage.y = 0.0;
		get_line(info);
		info->x += 1;
		swap_decimals(info->decimals, decimal_storage);
		info->startpoint.current = info->actual.current;
		info->startpoint.line = info->actual.line;
		while (info->y + 1 < info->size)
		{
			get_column(info);
			info->y += 1;
		}
		swap_decimals(info->decimals, decimal_storage);
		info->actual.current = info->startpoint.current;
		info->actual.line = info->startpoint.line;
	}	
}

int fill_image(struct info *info)
{
	struct point save;

	info->actual.current = info->startpoint.current;
	info->actual.line = info->startpoint.line;
	save.current = info->startpoint.current;
	save.line = info->startpoint.line;
	draw_lines(info);
	info->actual.current = save.current;
	info->actual.line = save.line;
	draw_columns(info);
	return 0;
}



/*
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
	return 0;
}
*/
