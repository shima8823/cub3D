/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:42:45 by shima             #+#    #+#             */
/*   Updated: 2022/11/11 16:27:37 by shima            ###   ########.fr       */
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

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480
#define texWidth 64
#define texHeight 64

// 0x00FF0000
#define FLOOR_COLOR 16711680
// 0x000000FF
#define CEILING_COLOR 255


#define WINDOW_NAME "cub3D"

#define ERR_MSG_ARGC "Usage: ./cub3D Filename"
#define ERR_MSG_FILE_NAME "File names must end with .cub"
#define ERR_MSG_LINE_INFO_NUM "One line must be two pieces of information separated by a space"
# define ERR_MSG_INVALID_ID "File structure:\nNO ./path_to_the_north_texture\n\
SO ./path_to_the_south_texture\n\
WE ./path_to_the_west_texture\n\
EA ./path_to_the_east_texture\n\
\n\
F 220,100,0\n\
C 225,30,0\n"
# define ERR_MSG_INVALID_MAP 





typedef enum e_type
{
	NEUTRAL,
	TEXTURE_MODE,
	COLOR_MODE,
	MAP_MODE
} t_type;

typedef struct s_img
{
	void	*img;
	int	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		width;
	int		height;
} t_img;

typedef struct s_game_info
{
	void	*mlx_ptr;
	void	*win_ptr;

	//x and y start position
	// 変更するのはW Sを押した時だけ
	double posX;
	double posY;
	//initial direction vector
	// 変更するのはA Dを押した時だけ
	double dirX; // -1
	double dirY; // 0
	//the 2d raycaster version of camera plane
	// 変更するのはA Dを押した時だけ
	double planeX; // 0
	double planeY; // 0.66

	int	buffer[screenHeight][screenWidth];
	int	texture[8][texWidth * texHeight];

	// speed modifiers
	double moveSpeed;
	double rotSpeed;

	t_img	img;

	char *texture_path[4];

	char *floor_ceiling_color[2];

} t_game_info;

typedef struct s_file_parse
{
	int		fd;
	t_type	state;
	int		texture_index;
	int		floor_ceiling_index;
	char	texture_id[4][3];
	char	floor_ceiling_id[2][2];
} t_file_parse;

void	read_file(t_game_info *info, char *path);
void	error_exit(char *err_msg);

#endif