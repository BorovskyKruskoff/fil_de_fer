#include "fdf.h"

void		put_pixel(char *image, struct point *actual, char *color)
{
	int		sizeline;

	sizeline = 3 * WINLEN;
	if (actual->current >= sizeline * actual->line &&
		actual->current <= sizeline * (actual->line + 1))
	{
		image[actual->current] = (char)255;
		actual->current++;
		image[actual->current] = (char)255;
		actual->current++;
		image[actual->current] = (char)255;
		actual->current++;
	}
	printf("%d\n", sizeof(char));
}

int		get_colors(int argc, char **argv, struct info *info)
{
	return 1;
}
