/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:42:06 by mhida             #+#    #+#             */
/*   Updated: 2022/11/14 16:00:11 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	press_left_arrow(t_game_info *info)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = info->dir_x;
	info->dir_x = info->dir_x * cos(info->rot_speed) - \
		info->dir_y * sin(info->rot_speed);
	info->dir_y = old_dir_x * sin(info->rot_speed) + \
		info->dir_y * cos(info->rot_speed);
	old_plane_x = info->plane_x;
	info->plane_x = info->plane_x * cos(info->rot_speed) - \
		info->plane_y * sin(info->rot_speed);
	info->plane_y = old_plane_x * sin(info->rot_speed) + \
		info->plane_y * cos(info->rot_speed);
}

void	press_right_arrow(t_game_info *info)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = info->dir_x;
	info->dir_x = info->dir_x * cos(-(info->rot_speed)) - \
		info->dir_y * sin(-(info->rot_speed));
	info->dir_y = old_dir_x * sin(-(info->rot_speed)) + \
		info->dir_y * cos(-(info->rot_speed));
	old_plane_x = info->plane_x;
	info->plane_x = info->plane_x * cos(-(info->rot_speed)) - \
		info->plane_y * sin(-(info->rot_speed));
	info->plane_y = old_plane_x * sin(-(info->rot_speed)) + \
		info->plane_y * cos(-(info->rot_speed));
}

int	press_x(void)
{
	exit(EXIT_SUCCESS);
}
