#include "fdf.h"

static void	prepare_draw(struct point *actual, struct info *info,
			struct vectors *is_pos, float ratio)
{
	struct vectors	*inc;

	inc->x += info->angle.x info->decimals.x;
	inc->y += info->angle.y + info->decimals.y;
	




	info->decimals.x = inc->x;
	info->decimals.y = inc->y;
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
	{
	if (info->angle.y < 0.0)
	{
		is_pos->y = -1;
		info->angle.y = -1;
	{
	ratio = info->angle.x / info->angle.y;
	prepare_draw(actual, info, is_pos, ratio);
}
