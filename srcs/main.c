#include "fdf.h"

static void other_keys(int keycode, struct info *info)
{
	if (keycode == 114)
		printf("Reset !\n");
	if (keycode == 65361)
		printf("Left !\n");
	if (keycode == 65363)
		printf("Right !\n");
	if (keycode == 65364)
		printf("Down !\n");
	if (keycode == 65362)
		printf("Up !\n");
	if (keycode == 65307)
		exit(0);
}

static int key_management(int keycode, void *param)
{
	struct info	*info;

	info = (struct info*)param;
	printf("The key pressed is : %d\n.", keycode);
	if (keycode == 113)
		info->rot_z -= M_PI / 8;
	else if (keycode == 119)
		info->rot_y += M_PI / 8;
	else if (keycode == 101)
		info->rot_z += M_PI / 8;
	else if (keycode == 97)
		info->rot_x -= M_PI / 8;
	else if (keycode == 115)
		info->rot_y -= M_PI / 8;
	else if (keycode == 100)
		info->rot_x += M_PI / 8;
	else
		other_keys(keycode, info);
	printf("z = %lf\ny = %lf\n", info->rot_z, info->rot_y);
	if (!(fill_image(info)))
		return 1;
	return 0;
}

int main(int argc, char **argv)
{
	struct info	*info;
	void		*mlx;
	void		*win;

	
	if (!(info = (struct info*)malloc(sizeof(struct info))))
		return (display_error(0));
	if (error_management(argv, argc, info) || check_winsize())
		return (1);
	mlx = mlx_init();
	win = mlx_new_window(mlx, WINLEN, WINHEIGHT, "FdF ~ ggay");
	info->mlx = mlx;
	info->win = win;
	info->rot_x = 0.0;
	info->rot_y = 0.0;
	info->rot_z = 0.0;
	info->pos_x = 200;
	info->pos_y = 0;
	info->pos_z = 0;
	info->height = 1;
	if (!(create_image(info)))
		return (display_error(0));
	mlx_key_hook(win, key_management, (void*)info);
	mlx_loop(mlx);
	return 0;
}
