#include "fdf.h"

static void get_max_min(struct info *info)
{
	int max;
	int min;
	int a;
	int b;

	max = -2147483648;
	min = 2147483647;
	a = 0;
	while (a < info->size)
	{
		b = 0;
		while (b < info->size)
		{
			if (info->tab[a][b] > max)
				max = info->tab[a][b];
			if (info->tab[a][b] < min)
				min = info->tab[a][b];
			b++;
		}
		a++;
	}
	info->min = (double)min;
	info->max = (double)max;
}

static double prepare_fill(struct info *info, int btp)
{
	if (WINHEIGHT > WINLEN)
		info->minsize = WINLEN;
	else
		info->minsize = WINHEIGHT;
	info->gap = ((info->minsize / 1.2) + info->pos_z) / info->size;
	info->sizeline = 4 * WINLEN;
	get_max_min(info);
	return 1;
}

static void update_info(struct info *info)
{
	if (info->rot_x >= M_PI * 2)
		info->rot_x -= M_PI * 2;
	if (info->rot_x < 0)
		info->rot_x += M_PI * 2;
	if (info->rot_y >= M_PI * 2)
		info->rot_y -= M_PI * 2;
	if (info->rot_y < 0)
		info->rot_y += M_PI * 2;
	if (info->rot_z >= M_PI * 2)
		info->rot_z -= M_PI * 2;
	if (info->rot_z < 0)
		info->rot_z += M_PI * 2;
	if (info->pos_x >= 2500)
		info->pos_x -= 100;
	if (info->pos_x <= -2500)
		info->pos_x += 100;
	if (info->pos_y >= 2500)
		info->pos_y -= 100;
	if (info->pos_y <= -2500)
		info->pos_y += 100;
}

double start_fill(struct info *info)
{
	int line_angle = (WINHEIGHT / 2) * cos(info->rot_z - M_PI * 0.75);
	int current_angle = (WINLEN / 2) * cos(info->rot_z - M_PI * 1.25);

	update_info(info);
	info->vectors_hor.x = cos(info->rot_x) * cos(info->rot_z);
	info->vectors_hor.y = cos(info->rot_x) * sin(info->rot_z + M_PI);
	info->vectors_vert.x = cos(info->rot_y) * sin(info->rot_z);
	info->vectors_vert.y = cos(info->rot_y) * cos(info->rot_z);
	info->y = 0;
	info->x = 0;
	info->rest.x = 0.0;
	info->rest.y = 0.0;
	info->transition = 0;
	info->decimals.x = 0.0;
	info->decimals.y = 0.0;
	info->startpoint.line = (WINHEIGHT / 2) + line_angle + info->pos_y;
	info->startpoint.current = ((WINLEN / 2) + current_angle) * 4
		+ (info->startpoint.line * 4 * WINLEN) + (info->pos_x * 4);

	fill_image(info);
	mlx_put_image_to_window((void*)info->mlx, (void*)info->win,
		(void*)info->image_pointer, 0, 0);
	return 0;
}

double			create_image(struct info *info)
{
	int size_line;
	int endian;
	int btp;

	btp = 24;
	size_line = WINLEN * 4;
	endian = 0;
	info->image_pointer = mlx_new_image(info->mlx, WINLEN, WINHEIGHT);
	info->image = mlx_get_data_addr
		(info->image_pointer, &(btp), &(size_line), &(endian));
	info->btp = btp;
	info->sizeline = size_line;
	
//	printf("%d\n", info->sizeline);
//	printf("%d\n", info->btp);
	if (!(prepare_fill(info, btp)))
		return 0;
	start_fill(info);
	return 1;
}
