#include "fdf.h"

//x and y will equal 1 if a line or column need to be drawn respectively
//otherwise anything else is ignored and draws nothing

void	draw(struct info *info, int x, int y, struct vectors *rest)
{
	rest->x -= x;
	rest->y -= y;
	if (x == 1)
		info->actual.current += (3 * info->is_pos.x);
	if (y == 1)
	{
		info->actual.current += (WINLEN * 3 * info->is_pos.y);
		info->actual.line += (1 * info->is_pos.y);
	}


	printf("X : %d",(info->actual.current -
		info->sizeline * info->actual.line) / 3);
	printf("    Y : %d\n", info->actual.line);
//	mlx_pixel_put(info->mlx, info->win,
//	(info->actual.current - (info->sizeline * info->actual.line)) / 3,
//	info->actual.line, 16777215);
//
	put_pixel(info, &info->actual, 16777215);
}

void	prepare_draw_big(struct info *info, struct vectors *rest ,double ratio)
{
	double	x_total;
	double	y_total;
	double	x;
	double	y;

	x_total = 0.0;
	y_total = 0.0;
	while (x_total < rest->x && y_total < rest->y)
	{
		printf("X = %lf\nY = %lf\n", x, y);
		x += info->angle.x;
		y += info->angle.y;
		while (x >= 1.0 && x_total < rest->x &&
			y >= 1.0 && y_total < rest->y)
		{
			draw(info, 1, 1, rest);
			x_total += 1;
			y_total += 1;
			x -= 1;
			y -= 1;
		}
		while (x >= 1.0 && x_total < rest->x)
		{
			draw(info, 1, 0, rest);
			x_total += 1;
			x -= 1;
		}
		while (y >= 1.0 && y_total < rest->y)
		{
			draw(info, 0, 1, rest);
			y_total += 1;
			y -= 1;
		}
	}
}

 void	prepare_draw(struct info *info, struct vectors *rest, double ratio)
{
	if (rest->x >= 1.0 && rest->y >= 1.0)
		prepare_draw_big(info, rest, ratio);
	else
	{
		while(rest->x >= 1.0)
			draw(info, 1, 0, rest);
		while(rest->y >= 1.0)
			draw(info, 0, 1, rest);
	}
	info->decimals.x = rest->x;
	info->decimals.y = rest->y;
}

int	trace(struct info *info)
{
	struct vectors	*rest;
	double		ratio;

	if (!(rest = (struct vectors*)malloc(sizeof(struct vectors))))
		return 1;
	rest->x = 0.0;
	rest->y = 0.0;
	info->is_pos.x = 1;
	info->is_pos.y = 1;
	if (info->angle.x < 0.0)
	{
		info->is_pos.x = -1;
		info->angle.x *= -1;
	}
	if (info->angle.y < 0.0)
	{
		info->is_pos.y = -1;
		info->angle.y *= -1;
	}
	ratio = info->angle.x / info->angle.y;
	rest->x = (info->angle.x * info->gap) + info->decimals.x;
	rest->y = (info->angle.y * info->gap) + info->decimals.y;
	prepare_draw(info, rest, ratio);
	free(rest);
	return 1;
}
