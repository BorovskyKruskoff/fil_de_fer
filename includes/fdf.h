#ifndef FDF_H
# define FDF_H

# ifndef M_PI
#  define M_PI 3.14
# endif

# include "get_next_line.h"
# include <math.h>
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define WINLEN 800
# define WINHEIGHT 600

struct	vectors
{
	float			x;
	float			y;
};

struct	point
{
	double			current;
	double			line;
};

struct	color_node
{
	char			*color;
	struct s_colors		*next;
};

struct	info
{
	double			pos_x;
	double			pos_y;
	float			rot_x;
	float			rot_y;
	float			rot_z;
	double			height;
	double			transition;
	double			gap;
	double			minsize;
	double			btp;
	double			sizeline;
	double			max;
	double			min;
	double			y;
	double			x;
	struct vectors		vectors_hor;
	struct vectors		vectors_vert;
	struct vectors		angle;
	struct vectors		decimals;
	struct point		startpoint;
	void			*mlx;
	void			*win;
	char			*image;
	double			size;
	double			**tab;
	struct color_node	*colorlist;
};

void		trace(struct point *actual, struct info *info);
double		check_winsize(void);
double		start_fill(struct info *info);
double		fill_image(struct info *info);
double		put_pixel(double current, double line, double color);
double		create_image(struct info *info);
double		get_colors(int argc, char **argv, struct info *info);
double		create_tab(char *str, struct info *info, double size);
double		init_get_size(char *str);
double		display_error(int usage);
double		error_management(char **argv, int argc, struct info *info);
double		dif(struct info *info, double dir);

#endif
