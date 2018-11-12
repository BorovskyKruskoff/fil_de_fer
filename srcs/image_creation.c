#include "fdf.h"

static void	get_max_min(t_info *info)
{
	int		max;
	int		min;
	int		a;
	int		b;

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

static double	fill_arithmetic(t_info *info)
{
	if (!(info->vectors_hor = (t_vectors*)malloc(sizeof(t_vectors))))
		return (0);
	if (!(info->vectors_vert = (t_vectors*)malloc(sizeof(t_vectors))))
		return (0);
	if (!(info->angle_hor = (t_vectors*)malloc(sizeof(t_vectors))))
		return (0);
	if (!(info->angle_vert = (t_vectors*)malloc(sizeof(t_vectors))))
		return (0);
	return (1);
}

static double	prepare_fill(t_info *info, int btp)
{
	if (WINHEIGHT > WINLEN)
		info->minsize = WINLEN;
	else
		info->minsize = WINHEIGHT;
	info->gap = ((minsize / 1.2) + pos_z) / info->size;
	info->sizeline = btp * WINLEN;
	info->btp = btp;
	if (!(info->starpoint = (t_point)malloc(sizeof(t_point))))
		return (0);
	get_max_min(info);
	if (!(fill_arithmetic(info)))
		return  (0);
}

static void	update_info(t_info *info)
{
	if (info->rot_x >= 360)
		info->rot_x -= 360;
	if (info->rot_x < 0)
		info->rot_x += 360;
	if (info->rot_y >= 360)
		info->rot_y -= 360;
	if (info->rot_y < 0)
		info->rot_y += 360;
	if (info->rot_z >= 360)
		info->rot_z -= 360;
	if (info->rot_z < 0)
		info->rot_z += 360;
	if (info->pos_x >= 2500)
		info->pos_x -= 100;
	if (info->pos_x <= -2500)
		info->pos_x += 100;
	if (info->pos_y >= 2500)
		info->pos_y -= 100;
	if (info->pos_y <= -2500)
		info->pos_y += 100;
}

double			start_fill(t_info *info)
{
	update_info(info);
	info->vectors_hor->x = cos(info->rot_x) * cos(info->rot_z);
	info->vectors_hor->y = cos(info->rot_x) * sin(info->rot_z);
	info->vectors_vert->x = cos(info->rot_y) * sin(info->rot_z);
	info->vectors_vert->y = cos(info->rot_y) * cos(info->rot_z - 180);
	info->y = 0;
	info->x = 0;
	info->transition = 0;
\\	todo
	info->startpoint->line = 10 + info->pos_y;
	info->startpoint->current = (line * (3 * winlen)) + (info->pos_x * 3);
	fill_image(info);
}

double			create_image(t_info *info)
{
	void	*image_pointer;
	char	*image;
	double		size_line;
	double		endian;
	double		btp;

	btp = 8 * 3;
	size_line = (btp / 8) * WINLEN;
	endian = 0;
	image_pointer = mlx_new_image(info->mlx, WINLEN, WINHEIGHT);
	image = mlx_get_data_addr(image_pointer, &(btp), &(size_line), &(endian));
	info->image = image;
	if (!(prepare_fill(info, btp)))
		return (0);
	start_fill(info);
}
