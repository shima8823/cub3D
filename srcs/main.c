/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:41:15 by shima             #+#    #+#             */
/*   Updated: 2022/11/14 20:00:25 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/wrapper_mlx.h"

static void	draw(t_game_info *info)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			info->img.addr[y * SCREEN_WIDTH + x] = info->buffer[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img.img, 0, 0);
}

static void	calc(t_game_info *info)
{
	t_calc_info	calc_info;

	calc_info.x = 0;
	while (calc_info.x < SCREEN_WIDTH)
	{
		set_calc_info(info, &calc_info);
		set_step_and_side_dist(info, &calc_info);
		dda(info, &calc_info);
		set_perp_wall_dist(&calc_info);
		calc_info.line_height = (int)(SCREEN_HEIGHT / calc_info.perp_wall_dist);
		set_draw_start_and_end(&calc_info);
		set_tex_num(info, &calc_info);
		set_wall_x(info, &calc_info);
		set_tex_x_coordinate(&calc_info);
		set_step_and_tex_pos(&calc_info);
		ceiling_casting(info, &calc_info);
		calc_info.y = calc_info.draw_start;
		set_tex_color_to_buffer(info, &calc_info);
		floor_casting(info, &calc_info);
		calc_info.x++;
	}
}

static int	main_loop(t_game_info *info)
{
	calc(info);
	draw(info);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_game_info	info;

	if (argc != 2)
		error_exit(ERR_MSG_ARGC);
	if (!is_valid(argv[1]))
		error_exit(ERR_MSG_FILE_NAME);
	ft_bzero(&info, sizeof(t_game_info));
	read_file(&info, argv[1]);
	init_game_info(&info);
	mlx_loop_hook(info.mlx_ptr, &main_loop, &info);
	mlx_hook(info.win_ptr, X_EVENT_KEY_PRESS, X_EVENT_KEY_PRESS_MASK, \
		&key_press, &info);
	mlx_hook(info.win_ptr, 33, 1L << 17, &press_x, NULL);
	mlx_loop(info.mlx_ptr);
}
