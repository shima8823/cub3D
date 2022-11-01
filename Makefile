CFLAGS = 
# CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -Iincludes
LDFLAGS = -L$(LIBFT_DIR) -L$(MINILIBX_DIR) -L/usr/X11R6/lib
LDLIBS = -lft -lmlx_Darwin -lX11 -lXext -framework OpenGL -framework AppKit
NAME = cub3D
SRCS =	main.c
OBJS = $(addprefix $(OBJSDIR)/, $(SRCS:%.c=%.o))
OBJSDIR = objs
VPATH = srcs 

## libft ##
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
###########

## minilibx ##
MINILIBX_DIR = minilibx-linux
MINILIBX = $(MINILIBX_DIR)/libmlx_Darwin.a
##############

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJS)
	$(CC) $(LDFLAGS) -o $(NAME) $(OBJS) $(LDLIBS)

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