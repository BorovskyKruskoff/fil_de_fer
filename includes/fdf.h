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

typedef struct			s_vectors
{
	double			x;
	double			y;
}				t_vectors;

typedef struct			s_point
{
	double			current;
	double			line;
}				t_point;

typedef struct			s_colors
{
	char			*color;
	struct s_colors		*next;
}				t_colors;

typedef struct			s_info
{
	double			pos_x;                  x
	double			pos_y;                  x
	double			pos_z                   x
	double			rot_x;                  x
	double			rot_y;                  x
	double			rot_z;                  x
	double			height;                 x
	double			transition;             x
	double			gap;                    x
	double			minsize;                x
	double			btp;                    x
	double			sizeline;               x
	double			max;                    x
	double			min;                    x
	double			y;                      x
	double			x;                      x
	t_vectors		*vectors_hor;           x
	t_vectors		*vectors_vert;          x
	t_vectors		*angle;                 x
	t_point			startpoint;
	void			*mlx;                   x
	void			*win;                   x
	char			*image;                 x
	double			size;                   x
	double			**tab;                  x
	t_colors		*colorlist;             x
}				t_info;

t_point		trace_tleft(double current, double line, t_info *info);
t_point		trace_bleft(double current, double line, t_info *info);
t_point		trace_tright(double current, double line, t_info *info);
t_point		trace_bright(double current, double line, t_info *info);
double		check_winsize(void);
double		start_fill(t_info *info);
double		fill_image(t_info *info);
double		put_pixel(double current, double line, double color);
double		create_image(t_info *info);
double		get_colors(int argc, char **argv, t_info *info);
double		create_tab(char *str, t_info *info, double size); 
double		init_get_size(char *str);
double		display_error(int usage);
double		error_management(char **argv, int argc, t_info *info);
double		dif(t_info *info, double dir);

#endif
