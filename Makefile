NAME := fdf

MLX_LIB := -L src/minilibx-linux -l mlx

FT_LIB := -L src/libft_ultra -l ft

X_LIB := -L /usr/lib -l Xext -l X11 -l z -l m

INC := -I /usr/include

LIBS := $(MLX_LIB) $(FT_LIB) $(X_LIB)

CC := cc

CFLAGS := -Wall -Werror -Wextra -g

SRC := main.c\
		window_draw.c\
		window_prep.c\
		handle_input1.c\
		handle_input2.c\
		utils1.c\
		utils2.c\
		free_stuff.c\
		events1.c\
		events2.c

O_PATH := ./obj/

vpath %.c src

OBJ := $(SRC:%.c=$(O_PATH)%.o)

$(O_PATH)%.o:%.c
	mkdir -p obj 
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	echo "compiling..."
	$(MAKE) -C src/libft_ultra/
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(INC) $(LIBS)
	echo "executable was created."

clean:
	$(MAKE) clean -C src/libft_ultra/
	rm -rf -d $(O_PATH)
	echo ".o files were deleted."

fclean: clean
	$(MAKE) fclean -C src/libft_ultra/
	rm -f $(NAME)
	echo "executable was deleted."

re:	fclean all

norm:
	norminette -R CheckForbiddenSourceHeader src/*.c src/fdf.h

.PHONY: all clean fclean re norm

.SILENT: 
