CFLAGS = 
# CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -Iincludes
LDFLAGS = -L$(LIBFT_DIR)
LDLIBS = -lft
NAME = cub3D
SRCS =	main.c

OBJS = $(addprefix $(OBJSDIR)/, $(SRCS:%.c=%.o))
OBJSDIR = objs
VPATH = srcs 

## libft ##
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
###########

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(LDFLAGS) -o $(NAME) $(OBJS) $(LDLIBS)

$(LIBFT):
	make bonus -C $(LIBFT_DIR)

$(OBJSDIR)/%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(NAME)

re: fclean all