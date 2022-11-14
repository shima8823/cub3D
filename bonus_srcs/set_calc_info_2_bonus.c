/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_calc_info_2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:59:30 by mhida             #+#    #+#             */
/*   Updated: 2022/11/14 22:11:58 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	set_step_and_tex_pos(t_calc_info *calc_info)
{
	calc_info->step = 1.0 * TEX_HEIGHT / calc_info->line_height;
	calc_info->tex_pos = (calc_info->draw_start - SCREEN_HEIGHT / 2 \
		+ calc_info->line_height / 2) * calc_info->step;
}

void	set_tex_x_coordinate(t_calc_info *calc_info)
{
	calc_info->tex_x = (int)(calc_info->wall_x * (double)TEX_WIDTH);
	if (calc_info->side == 0 && calc_info->ray_dir_x > 0)
		calc_info->tex_x = TEX_WIDTH - calc_info->tex_x - 1;
	if (calc_info->side == 1 && calc_info->ray_dir_y < 0)
		calc_info->tex_x = TEX_WIDTH - calc_info->tex_x - 1;
}

void	set_wall_x(t_game_info *info, t_calc_info *calc_info)
{
	if (calc_info->side == 0)
		calc_info->wall_x = \
		info->pos_y + calc_info->perp_wall_dist * calc_info->ray_dir_y;
	else
		calc_info->wall_x = \
		info->pos_x + calc_info->perp_wall_dist * calc_info->ray_dir_x;
	calc_info->wall_x -= floor(calc_info->wall_x);
}

void	set_tex_num(t_game_info *info, t_calc_info*calc_info)
{
	calc_info->tex_num = info->map[calc_info->map_x][calc_info->map_y] - '0';
	if (!(calc_info->tex_num == 1 || calc_info->tex_num == 0))
		calc_info->tex_num = 0;
}
