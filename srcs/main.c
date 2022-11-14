/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:41:15 by shima             #+#    #+#             */
/*   Updated: 2022/11/14 14:39:51 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/wrapper_mlx.h"

void	init_game_info(t_game_info *info);
int		main_loop(t_game_info *info);
int		key_press(int keycode, t_game_info *info);

void	load_texture(t_game_info *info);
void	load_image(void *mlx_ptr, int *texture, char *path);

bool	is_valid(char *path);

int	press_x()
{
	exit(0);
}

int main(int argc, char *argv[])
{
	t_game_info	info;

	if (argc != 2)
		error_exit(ERR_MSG_ARGC);
	if (is_valid(argv[1]))
		error_exit(ERR_MSG_FILE_NAME);
	ft_bzero(&info, sizeof(t_game_info));
	read_file(&info, argv[1]);
	init_game_info(&info);
	mlx_loop_hook(info.mlx_ptr, &main_loop, &info);
	mlx_hook(info.win_ptr, X_EVENT_KEY_PRESS, X_EVENT_KEY_PRESS_MASK, &key_press, &info);
	mlx_hook(info.win_ptr, 33, 1L << 17, &press_x, NULL);
	mlx_loop(info.mlx_ptr);
}

bool	is_valid(char *path)
{
	char *s;

	s = ft_strrchr(path, '.');
	if (!s || ft_strncmp(s, ".cub", 5) != 0)
		return (true);
	return (false);
}

void	init_game_info(t_game_info *info)
{
	info->mlx_ptr = wmlx_init();
	info->win_ptr = wmlx_new_window(info->mlx_ptr, screenWidth, screenHeight, WINDOW_NAME);
	info->posX += 0.5;
	info->posY += 0.5;
	init_player_dir(info);
	info->moveSpeed = 0.1;
	info->rotSpeed = 0.1;
	load_texture(info);
	info->img.img = wmlx_new_image(info->mlx_ptr, screenWidth, screenHeight);
	info->img.addr = (int *)wmlx_get_data_addr(info->img.img, &info->img.bits_per_pixel, &info->img.size_line, &info->img.endian);
}

void	load_texture(t_game_info *info)
{
	load_image(info->mlx_ptr, info->texture[0], info->texture_path[N]);
	load_image(info->mlx_ptr, info->texture[1], info->texture_path[S]);
	load_image(info->mlx_ptr, info->texture[2], info->texture_path[W]);
	load_image(info->mlx_ptr, info->texture[3], info->texture_path[E]);
}

void	load_image(void *mlx_ptr, int *texture, char *path)
{
	t_img	img;
	int x;
	int y;

	img.img = wmlx_xpm_file_to_image(mlx_ptr, path, &img.width, &img.height);
	img.addr = (int *)wmlx_get_data_addr(img.img, &img.bits_per_pixel, &img.size_line, &img.endian);
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

void	draw(t_game_info *info)
{
	int	x;
	int	y;

	y = 0;
	while (y < screenHeight)
	{
		x = 0;
		while (x < screenWidth)
		{
			info->img.addr[y * screenWidth + x] = info->buffer[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img.img, 0, 0);
}

void	calc(t_game_info *info)
{
	t_calc_info calc_info;

	calc_info.x = 0;
	while (calc_info.x < screenWidth)
	{
		set_calc_info(info, &calc_info);
		set_step_and_side_dist(info, &calc_info);
		dda(info, &calc_info);
		set_perp_wall_dist(&calc_info);
		calc_info.lineHeight = (int)(screenHeight / calc_info.perpWallDist);
		set_draw_start_and_end(&calc_info);
		set_tex_num(info, &calc_info);
		set_wall_x(info, &calc_info);
		set_tex_x_coordinate(&calc_info);
		set_step_and_tex_pos(&calc_info);
		ceiling_casting(info, &calc_info);
		calc_info.y = calc_info.drawStart;
		set_tex_color_to_buffer(info, &calc_info);
		floor_casting(info, &calc_info);
		calc_info.x++;
	}
}

int	main_loop(t_game_info *info)
{
	calc(info);
	draw(info);
	return (EXIT_SUCCESS);
}

int	key_press(int keycode, t_game_info *info)
{
	if (keycode == KEY_W)
	{
		if (info->map[(int)(info->posX + info->dirX * info->moveSpeed)][(int)info->posY] == '0')
			info->posX += info->dirX * info->moveSpeed;
		if (info->map[(int)info->posX][(int)(info->posY + info->dirY * info->moveSpeed)] == '0')
			info->posY += info->dirY * info->moveSpeed;
	}
	else if (keycode == KEY_S)
	{
		if (info->map[(int)(info->posX - info->dirX * info->moveSpeed)][(int)info->posY] == '0')
			info->posX -= info->dirX * info->moveSpeed;
		if (info->map[(int)info->posX][(int)(info->posY - info->dirY * info->moveSpeed)] == '0')
			info->posY -= info->dirY * info->moveSpeed;

	}
	else if (keycode == KEY_D)
	{
		if (info->map[(int)(info->posX)][(int)(info->posY + -(info->dirX) * info->moveSpeed)] == '0')
			info->posY += -(info->dirX) * info->moveSpeed;
		if (info->map[(int)(info->posX + info->dirY * info->moveSpeed)][(int)(info->posY)] == '0')
			info->posX += info->dirY * info->moveSpeed;
	}
	else if (keycode == KEY_A)
	{
		if (info->map[(int)(info->posX)][(int)(info->posY - -(info->dirX) * info->moveSpeed)] == '0')
			info->posY -= -(info->dirX) * info->moveSpeed;
		if (info->map[(int)(info->posX - info->dirY * info->moveSpeed)][(int)(info->posY)] == '0')
			info->posX -= info->dirY * info->moveSpeed;
	}
	else if (keycode == KEY_RIGHT_ARROW)
	{
		// both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-(info->rotSpeed)) - info->dirY * sin(-(info->rotSpeed));
		info->dirY = oldDirX * sin(-(info->rotSpeed)) + info->dirY * cos(-(info->rotSpeed));
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-(info->rotSpeed)) - info->planeY * sin(-(info->rotSpeed));
		info->planeY = oldPlaneX * sin(-(info->rotSpeed)) + info->planeY * cos(-(info->rotSpeed));
	}
	else if (keycode == KEY_LEFT_ARROW)
	{
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}
	else if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
