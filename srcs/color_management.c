#include "fdf.h"

static int verify(int current)
{
	int a = current % 4;

	return (current - a);
}

static int within_bounds(struct info *info, struct point *actual)
{
	if (actual->current < 0 || actual->current > info->sizeline * WINHEIGHT)
		return 0;
	if (actual->line < 0 || actual->line > WINHEIGHT)
		return 0;
	return 1;
}

void put_pixel(struct info *info, struct point *actual, int color)
{
	unsigned int uns_color = mlx_get_color_value(info->mlx, color);
	int sizeline;
	unsigned char color_part_R;
	unsigned char color_part_G;
	unsigned char color_part_B;

	actual->current = verify(actual->current);
	color_part_R = (unsigned char)uns_color;
	uns_color = uns_color >> 8;
	color_part_G = (unsigned char)uns_color;
	uns_color = uns_color >> 8;
	color_part_B = (unsigned char)uns_color;
	sizeline = 4 * WINLEN;
	if (actual->current >= sizeline * actual->line && actual->current
		<= sizeline * (actual->line + 1) && within_bounds(info, actual))
	{
		info->image[actual->current] = color_part_R;
		actual->current += 1;
		info->image[actual->current] = color_part_R;
		actual->current += 1;
		info->image[actual->current] = color_part_G;
		actual->current += 1;
		info->image[actual->current] = color_part_B;
		actual->current -= 3;
	}
}

int get_colors(int argc, char **argv, struct info *info)
{
	return 1;
}
