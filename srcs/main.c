#include "fdf.h"

static int		key_management(int keycode, void *param)
{
	t_info	*info;

	info = (t_info*)param;
	ft_putstr("The key pressed is : ");
	ft_putnbr(keycode);
	ft_putchar('\n');
	if (keycode == 0)
		ft_putstr("A !\n");
	if (keycode == 13)
		ft_putstr("W !\n");
	if (keycode == 2)
		ft_putstr("D !\n");
	if (keycode == 1)
		ft_putstr("S !\n");
	if (keycode == 15)
		ft_putstr("Reset !\n");
	if (keycode == 123)
		ft_putstr("Left !\n");
	if (keycode == 124)
		ft_putstr("Right !\n");
	if (keycode == 125)
		ft_putstr("Down !\n");
	if (keycode == 126)
		ft_putstr("Up !\n");
	if (keycode == 53)
		exit(0);
	if (!(start_fill(info)));
		return (1);
	return (0);
}

int				main(int argc, char **argv)
{
	t_info	*info;
	void	*mlx;
	void	*win;

	
	if (!(info = (t_info*)malloc(sizeof(t_info))))
		return (display_error(0));
	if (error_management(argv, argc, info) || check_winsize())
		return (1);
	mlx = mlx_init();
	win = mlx_new_window(mlx, WINLEN, WINHEIGHT, "FdF ~ ggay");
	info->mlx = mlx;
	info->win = win;
	info->rot_x = 0;
	info->rot_y = 0;
	info->rot_z = 0;
	info->pos_x = 0;
	info->pos_y = 0;
	info->pos_z = 0;
	info->height = 1;
	if (!(create_image(info)))
		return (display_error(0));
	mlx_key_hook(win, key_management, (void*)info);
	mlx_loop(mlx);
	return (0);
}
