/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:42:45 by shima             #+#    #+#             */
/*   Updated: 2022/11/14 16:25:09 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_RIGHT_ARROW 65363
# define KEY_LEFT_ARROW 65361

# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

# define MAP_X_LIMIT 200
# define MAP_Y_LIMIT 200

# define MAX_X MAP_X_LIMIT + 1
# define MAX_Y MAP_Y_LIMIT + 1

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_PRESS_MASK 1L

# define WINDOW_NAME "cub3D"

# define ERR_MSG_ARGC "Usage: ./cub3D Filename"
# define ERR_MSG_FILE_NAME "File names must end with .cub"
# define ERR_MSG_INVALID_ID "File structure:\nNO ./path_to_the_north_texture\n\
SO ./path_to_the_south_texture\n\
WE ./path_to_the_west_texture\n\
EA ./path_to_the_east_texture\n\
\n\
F 220,100,0\n\
C 225,30,0\n\n\
11111\n10001\n10N01\n10001\n11111"
# define ERR_MSG_INVALID_CHAR "The letter of the map must be one of ' ' '0' '1' 'N' 'S' 'E' 'W'"
# define ERR_MSG_MULTIPLE_SPAWN "There must be one spawn position"
# define ERR_MSG_COLOR_CHAR "color must be numeric"
# define ERR_MSG_COLOR_RANGE "R,G,B colors in range [0,255]"
# define ERR_MSG_MAP_SIZE "Map size must be within 500 x 500"

typedef enum e_dir
{
	N,
	S,
	W,
	E
}	t_dir;

typedef enum e_player_dir
{
	DIR_X,
	DIR_Y,
	PLANE_X,
	PLANE_Y
}	t_player_dir;

typedef enum e_type
{
	NEUTRAL,
	TEXTURE_MODE,
	COLOR_MODE,
	MAP_MODE
}	t_type;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_game_info
{
	void			*mlx_ptr;
	void			*win_ptr;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	int				buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	int				texture[8][TEX_WIDTH * TEX_HEIGHT];
	double			move_speed;
	double			rot_speed;
	t_img			img;
	t_img			north_tex;
	t_img			south_tex;
	t_img			west_tex;
	t_img			east_tex;
	char			*texture_path[4];
	char			*floor_ceiling_color[2];
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	char			spawn_dir;
	int				map_size_y;
	int				map_size_x;
	char			map[MAX_Y][MAX_X];
}	t_game_info;

typedef struct s_file_parse
{
	int		fd;
	t_type	state;
	bool	skip_empty_line;
	bool	exists_nl_end_of_map;
	int		texture_index;
	int		floor_ceiling_index;
	char	texture_id[4][3];
	char	floor_ceiling_id[2][2];
}	t_file_parse;

typedef struct s_calc_info
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		y;
	int		x;
	int		tex_y;
	int		color;
}	t_calc_info;

void			read_file(t_game_info *info, char *path);
void			error_exit(char *err_msg);
int				count_array(char **split_line);
bool			is_valid(char *path);
void			init_game_info(t_game_info *info);
int				key_press(int keycode, t_game_info *info);
int				press_x(void);
void			press_w(t_game_info *info);
void			press_s(t_game_info *info);
void			press_d(t_game_info *info);
void			press_a(t_game_info *info);
void			press_right_arrow(t_game_info *info);
void			press_left_arrow(t_game_info *info);
unsigned int	get_color(char *line);
void			init_player_dir(t_game_info *info);
void			flood_fill(t_game_info *info);
void			set_calc_info(t_game_info *info, t_calc_info *calc_info);
void			set_step_and_side_dist(t_game_info *info, \
	t_calc_info *calc_info);
void			dda(t_game_info *info, t_calc_info *calc_info);
void			set_perp_wall_dist(t_calc_info *calc_info);
void			set_draw_start_and_end(t_calc_info*calc_info);
void			set_tex_num(t_game_info *info, t_calc_info*calc_info);
void			set_wall_x(t_game_info *info, t_calc_info *calc_info);
void			set_tex_x_coordinate(t_calc_info *calc_info);
void			set_step_and_tex_pos(t_calc_info *calc_info);
void			ceiling_casting(t_game_info *info, t_calc_info *calc_info);
void			set_tex_color_to_buffer(t_game_info *info, \
	t_calc_info *calc_info);
void			floor_casting(t_game_info *info, t_calc_info *calc_info);

#endif