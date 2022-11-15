CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -Iincludes
LDFLAGS = -L$(LIBFT_DIR) -L$(MINILIBX_DIR)
LDLIBS = -lft -lm
NAME = cub3D
NAME_BONUS = cub3D_bonus
SRCS =	main.c utils.c flood_fill.c set_calc_info.c set_calc_info_2.c dda.c \
		casting.c  is_valid.c init_game_info.c key_press.c \
		key_press_2.c key_press_3.c  \
		read_file.c parse_line.c parse_map.c parse_texture_color.c get_color.c init_player_direction.c\
		wmlx_get_data_addr.c wmlx_init.c wmlx_new_image.c wmlx_new_window.c wmlx_xpm_file_to_image.c

OBJS = $(addprefix $(OBJSDIR)/, $(SRCS:%.c=%.o))
OBJSDIR = objs
VPATH = srcs srcs/wrapper_mlx srcs/read_file srcs/utils bonus_srcs

SRCS_BONUS = minimap_bonus.c main_bonus.c utils_bonus.c flood_fill_bonus.c set_calc_info_bonus.c \
		set_calc_info_2_bonus.c dda_bonus.c casting_bonus.c is_valid_bonus.c \
		init_game_info_bonus.c key_press_bonus.c key_press_2_bonus.c key_press_3_bonus.c \
		read_file_bonus.c parse_line_bonus.c parse_map_bonus.c parse_texture_color_bonus.c \
		get_color_bonus.c init_player_direction_bonus.c wmlx_get_data_addr_bonus.c \
		wmlx_init_bonus.c wmlx_new_image_bonus.c wmlx_new_window_bonus.c \
		wmlx_xpm_file_to_image_bonus.c
OBJS_BONUS = $(addprefix $(OBJS_BONUS_DIR)/, $(SRCS_BONUS:.c=.o))
OBJS_BONUS_DIR = bonus_srcs

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

ifdef WITH_BONUS
OBJS = $(OBJS_BONUS)
NAME = $(NAME_BONUS)
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
	$(RM) $(OBJS) $(OBJS_BONUS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(LIBFT)
	make clean -C $(MINILIBX_DIR)
	$(RM) $(NAME) $(NAME_BONUS)

test:
	test/test.sh

re: fclean all

bonus:
	@make WITH_BONUS=1

.PHONY: all clean fclean re bonus test
