CFLAGS =
# CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -Iincludes
LDFLAGS = -L$(LIBFT_DIR) -L$(MINILIBX_DIR)
LDLIBS = -lft -lm
NAME = cub3D
SRCS =	main.c utils.c flood_fill.c set_calc_info.c set_calc_info_2.c dda.c \
		casting.c  is_valid.c init_game_info.c key_press.c \
		key_press_2.c key_press_3.c  \
		read_file.c parse_line.c parse_map.c parse_texture_color.c get_color.c init_player_direction.c\
		wmlx_get_data_addr.c wmlx_init.c wmlx_new_image.c wmlx_new_window.c wmlx_xpm_file_to_image.c

OBJS = $(addprefix $(OBJSDIR)/, $(SRCS:%.c=%.o))
OBJSDIR = objs
VPATH = srcs srcs/wrapper_mlx srcs/read_file srcs/utils

## libft ##
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
###########

## minilibx ##
MINILIBX_DIR = minilibx-linux
MINILIBX = $(MINILIBX_DIR)/libmlx_Linux.a
##############

ifeq ($(shell uname), Darwin)
MINILIBX = $(MINILIBX_DIR)/libmlx_Darwin.a
LDFLAGS += -L/usr/X11R6/lib
LDLIBS += -lmlx_Darwin -framework OpenGL -framework AppKit -lXext -lX11
else
LDFLAGS += -L/usr/lib
LDLIBS += -lmlx_Linux -lXext -lX11
endif

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) $(LDLIBS)

$(LIBFT):
	make bonus -C $(LIBFT_DIR)

$(MINILIBX):
	make -C $(MINILIBX_DIR)

$(OBJSDIR)/%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(LIBFT)
	make clean -C $(MINILIBX_DIR)
	$(RM) $(NAME)

.PHONY: test
test:
	test/test.sh

re: fclean all