/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_calc_info_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:59:30 by mhida             #+#    #+#             */
/*   Updated: 2022/11/14 22:12:03 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	set_draw_start_and_end(t_calc_info*calc_info)
{
	calc_info->draw_start = -(calc_info->line_height) / 2 + SCREEN_HEIGHT / 2;
	if (calc_info->draw_start < 0)
		calc_info->draw_start = 0;
	calc_info->draw_end = calc_info->line_height / 2 + SCREEN_HEIGHT / 2;
	if (calc_info->draw_end >= SCREEN_HEIGHT)
		calc_info->draw_end = SCREEN_HEIGHT;
}

void	set_perp_wall_dist(t_calc_info *calc_info)
{
	if (calc_info->side == 0)
		calc_info->perp_wall_dist = \
		(calc_info->side_dist_x - calc_info->delta_dist_x);
	else
		calc_info->perp_wall_dist = \
		(calc_info->side_dist_y - calc_info->delta_dist_y);
}

void	set_step_and_side_dist(t_game_info *info, t_calc_info *calc_info)
{
	if (calc_info->ray_dir_x < 0)
	{
		calc_info->step_x = -1;
		calc_info->side_dist_x = \
			(info->pos_x - calc_info->map_x) * calc_info->delta_dist_x;
	}
	else
	{
		calc_info->step_x = 1;
		calc_info->side_dist_x = \
			(calc_info->map_x + 1.0 - info->pos_x) * calc_info->delta_dist_x;
	}
	if (calc_info->ray_dir_y < 0)
	{
		calc_info->step_y = -1;
		calc_info->side_dist_y = \
			(info->pos_y - calc_info->map_y) * calc_info->delta_dist_y;
	}
	else
	{
		calc_info->step_y = 1;
		calc_info->side_dist_y = \
			(calc_info->map_y + 1.0 - info->pos_y) * calc_info->delta_dist_y;
	}
}

void	set_calc_info(t_game_info *info, t_calc_info *calc_info)
{
	calc_info->camera_x = 2 * calc_info->x / (double)SCREEN_WIDTH - 1;
	calc_info->ray_dir_x = info->dir_x + info->plane_x * calc_info->camera_x;
	calc_info->ray_dir_y = info->dir_y + info->plane_y * calc_info->camera_x;
	calc_info->map_x = (int)info->pos_x;
	calc_info->map_y = (int)info->pos_y;
	if (calc_info->ray_dir_x == 0)
		calc_info->delta_dist_x = 1e30;
	else
		calc_info->delta_dist_x = fabs(1 / calc_info->ray_dir_x);
	if (calc_info->ray_dir_y == 0)
		calc_info->delta_dist_y = 1e30;
	else
		calc_info->delta_dist_y = fabs(1 / calc_info->ray_dir_y);
	calc_info->hit = 0;
}
