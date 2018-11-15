#include "fdf.h"

void		put_pixel(char *image, struct point *actual, char *color)
{
	int		sizeline;

	sizeline = 3 * WINLEN;
	if (actual->current >= sizeline * actual->line &&
		actual->current <= sizeline * actual->line + 1)
	{
		image[actual->current] = color[0];
		actual->current++;
		image[actual->current] = color[1];
		actual->current++;
		image[actual->current] = color[2];
		actual->current++;
	}
}

int		get_colors(int argc, char **argv, struct info *info)
{
	return 1;
}
