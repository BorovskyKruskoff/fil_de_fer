#include "fdf.h"

double		display_error(int usage)
{
	if (usage == 1)
	{
		ft_putstr("usage: ./fdf file [colors]\nColors look like FFFFFF\n");
		return (1);
	}
	if (usage == 2)
	{
		ft_putstr("Les dimensions de la fenetre sont entre 200 et 2500\n");
		return (1);
	}
	ft_putstr("error\n");
	return (1);
}

double		error_management(char **argv, int argc, t_info *info)
{
	if (argc == 1)
		return (display_error(1));
	if (!(info->size = init_get_size(argv[1])))
		return (display_error(0));
	if (!(create_tab(argv[1], info, info->size)))
		return (display_error(0));
	if (!(get_colors(argc, argv, info)))
		return (display_error(1));
	return (0);
}

double		check_winsize(void)
{
	if (WINLEN > 2500 || WINHEIGHT > 2500)
		return (display_error(2));
	if (WINLEN < 200 || WINHEIGHT < 200)
		return (display_error(2));
	return (0);
}
