#ifndef FDF_H
# define FDF_H

# ifndef M_PI
#  define M_PI 3.1415926535
# endif

# include "get_next_line.h"
# include <ctype.h>
# include <math.h>
# include <mlx.h>
# include <fcntl.h>
# include <strings.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define WINLEN 800
# define WINHEIGHT 600

struct vectors
{
	double x;
	double y;
};

struct point
{
	int current;
	int line;
};

struct color_node
{
	char color[3];
	struct s_colors *next;
};

struct info
{
	double pos_x;
	double pos_y;
	double pos_z;
	double rot_x;
	double rot_y;
	double rot_z;
	double height;
	double gap;
	int minsize;
	int btp;
	int sizeline;
	int max;
	int min;
	int y;
	int x;
	int size;
	int **tab;
	int transition;
	struct point actual;
	struct vectors is_pos;
	struct vectors vectors_hor;
	struct vectors vectors_vert;
	struct vectors angle;
	struct vectors decimals;
	struct point startpoint;
	void *mlx;
	void *win;
	void *image_pointer;
	char *image;
	struct color_node *colorlist;
};

int trace(struct info *info);
void put_pixel(struct info *info, struct point *actual, int color);
double start_fill(struct info *info);
double create_image(struct info *info);
double dif(struct info *info, double dir);
int get_colors(int argc, char **argv, struct info *info);
int create_tab(char *str, struct info *info, int size);
int fill_image(struct info *info);
int init_get_size(char *str);
int display_error(int usage);
int error_management(char **argv, int argc, struct info *info);
int check_winsize(void);

#endif
