#include "fdf.h"

static void	prepare_draw(struct point *actual, struct info *info,
			struct vectors *is_pos, float ratio)
{
	printf("I dunno\n");
}

void		trace(struct point *actual, struct info *info)
{
	struct vectors	*is_pos;
	float		ratio;

	is_pos->x = 1;
	is_pos->y = 1;
	if (info->angle.x < 0.0)
	{
		is_pos->x = -1;
		info->angle.x = -1;
	}
	if (info->angle.y < 0.0)
	{
		is_pos->y = -1;
		info->angle.y = -1;
	}
	ratio = info->angle.x / info->angle.y;
	prepare_draw(actual, info, is_pos, ratio);
}
