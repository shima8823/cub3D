/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:42:45 by shima             #+#    #+#             */
/*   Updated: 2022/11/09 19:30:52 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
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
} t_game_info;


#endif