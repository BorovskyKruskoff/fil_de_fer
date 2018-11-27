NAME		= fdf
SRC_PATH	= srcs
SRC_NAME	= main.c\
		  get_next_line.c\
		  color_management.c\
		  error_management.c\
		  image_creation.c\
		  image_filling.c\
		  tab_setup.c\
		  line_tracing.c
SRC		= $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ_PATH	= objs
OBJ_NAME	= $(SRC_NAME:.c=.o)
OBJ		= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
INCLUDES	= -I includes
MLXFLAGS	= -lm -lmlx -lX11 -lXext
FLAGS		= -Wextra -Wall -std=c99
CFLAGS		= $(INCLUDES) $(FLAGS) $(MLXFLAGS)
CC		= gcc

all: $(NAME)

$(NAME): $(SRC)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -fv $(OBJ)
	rm -fv $(NAME)

re: fclean all

.PHONY: clean fclean re
