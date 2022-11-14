/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:20:48 by mhida             #+#    #+#             */
/*   Updated: 2022/11/14 16:39:51 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/wrapper_mlx.h"

static void	load_image(void *mlx_ptr, int *texture, char *path)
{
	t_img	img;
	int		x;
	int		y;

	img.img = wmlx_xpm_file_to_image(mlx_ptr, path, &img.width, &img.height);
	img.addr = (int *)wmlx_get_data_addr(img.img, \
		&img.bits_per_pixel, &img.size_line, &img.endian);
	y = 0;
	while (y < img.height)
	{
		x = 0;
		while (x < img.width)
		{
			texture[img.width * y + x] = img.addr[img.width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(mlx_ptr, img.img);
}

static void	load_texture(t_game_info *info)
{
	load_image(info->mlx_ptr, info->texture[0], info->texture_path[N]);
	load_image(info->mlx_ptr, info->texture[1], info->texture_path[S]);
	load_image(info->mlx_ptr, info->texture[2], info->texture_path[W]);
	load_image(info->mlx_ptr, info->texture[3], info->texture_path[E]);
}

void	init_game_info(t_game_info *info)
{
	info->mlx_ptr = wmlx_init();
	info->win_ptr = wmlx_new_window(info->mlx_ptr, SCREEN_WIDTH, \
		SCREEN_HEIGHT, WINDOW_NAME);
	info->pos_x += 0.5;
	info->pos_y += 0.5;
	init_player_dir(info);
	info->move_speed = 0.1;
	info->rot_speed = 0.1;
	load_texture(info);
	info->img.img = wmlx_new_image(info->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	info->img.addr = (int *)wmlx_get_data_addr(info->img.img, \
		&info->img.bits_per_pixel, &info->img.size_line, &info->img.endian);
}
