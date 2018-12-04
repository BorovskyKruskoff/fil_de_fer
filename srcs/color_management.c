#include "fdf.h"

static int verify(int current)
{
	int a = current % 3;

	return (current - a);
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
	sizeline = 3 * WINLEN;
	if (actual->current >= sizeline * actual->line && actual->line >= 0 &&
		actual->current <= sizeline * (actual->line + 1))
	{
		info->image[actual->current] = color_part_R;
		actual->current += 1;
		info->image[actual->current] = color_part_G;
		actual->current += 1;
		info->image[actual->current] = color_part_B;
		actual->current -= 2;
	}
}

int get_colors(int argc, char **argv, struct info *info)
{
	return 1;
}
