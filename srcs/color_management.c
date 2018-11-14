#include "fdf.h"

void		put_pixel(char *image, int current, int line, char *color)
{
	int		sizeline;

	sizeline = 3 * WINLEN;
	if (current >= sizeline * line && current <= sizeline * line + 1)
	{
		image[current] = color[0];
		current++;
		image[current] = color[1];
		current++;
		image[current] = color[2];
	}
}

int		get_colors(int argc, char **argv, struct info *info)
{
	return 1;
}
