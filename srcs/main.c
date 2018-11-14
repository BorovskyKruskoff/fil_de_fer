#include "fdf.h"

static int		key_management(int keycode, void *param)
{
	struct info	*info;

	info = (struct info*)param;
	printf("The key pressed is : %d\n.", keycode);
	if (keycode == 0)
		printf("A !\n");
	if (keycode == 13)
		printf("W !\n");
	if (keycode == 2)
		printf("D !\n");
	if (keycode == 1)
		printf("S !\n");
	if (keycode == 15)
		printf("Reset !\n");
	if (keycode == 123)
		printf("Left !\n");
	if (keycode == 124)
		printf("Right !\n");
	if (keycode == 125)
		printf("Down !\n");
	if (keycode == 126)
		printf("Up !\n");
	if (keycode == 53)
		exit(0);
	if (!(start_fill(info)))
		return 1;
	return 0;
}

int				main(int argc, char **argv)
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
	info->pos_x = 0;
	info->pos_y = 0;
	info->pos_z = 0;
	info->height = 1;
	if (!(create_image(info)))
		return (display_error(0));
	mlx_key_hook(win, key_management, (void*)info);
	mlx_loop(mlx);
	return 0;
}
