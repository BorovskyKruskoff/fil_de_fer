#include "fdf.h"

void		put_pixel(struct info *info, struct point *actual, int color)
{
	int		sizeline;

	sizeline = 3 * WINLEN;
	if (actual->current >= sizeline * actual->line && actual->line >= 0 &&
		actual->current <= sizeline * (actual->line + 1))
	{
		info->image[actual->current] =
			(char) mlx_get_color_value(info->mlx, color);
	}
}

int		get_colors(int argc, char **argv, struct info *info)
{
	return 1;
}
