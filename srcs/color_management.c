#include "fdf.h"

void put_pixel(struct info *info, struct point *actual, int color)
{
	int sizeline;
	char color_part_R;
	char color_part_G;
	char color_part_B;

	color_part_R = (char)color;
	color = color >> 8;
	color_part_G = (char)color;
	color = color >> 8;
	color_part_B = (char)color;
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
