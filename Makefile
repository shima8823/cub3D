CFLAGS = 
# CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -Iincludes
LDFLAGS = -L$(LIBFT_DIR) -L$(MINILIBX_DIR) 
LDLIBS = -lft -lm
NAME = cub3D
SRCS =	main.c read_file.c utils.c\
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

re: fclean all