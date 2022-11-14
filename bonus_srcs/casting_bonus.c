/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:59:18 by mhida             #+#    #+#             */
/*   Updated: 2022/11/14 22:07:53 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	floor_casting(t_game_info *info, t_calc_info *calc_info)
{
	while (calc_info->y < SCREEN_HEIGHT)
	{
		(info->buffer)[calc_info->y][calc_info->x] = info->floor_color;
		calc_info->y++;
	}
}

void	set_tex_color_to_buffer(t_game_info *info, t_calc_info *calc_info)
{
	while (calc_info->y < calc_info->draw_end)
	{
		calc_info->tex_y = (int)calc_info->tex_pos & (TEX_HEIGHT - 1);
		calc_info->tex_pos += calc_info->step;
		calc_info->color = 0;
		if (calc_info->tex_num == 1)
		{
			if (calc_info->side == 1 && calc_info->step_y == 1)
				calc_info->color = (info->texture)[W][TEX_HEIGHT * \
				calc_info->tex_y + calc_info->tex_x];
			else if (calc_info->side == 1 && calc_info->step_y == -1)
				calc_info->color = (info->texture)[E][TEX_HEIGHT * \
				calc_info->tex_y + calc_info->tex_x];
			else if (calc_info->side == 0 && calc_info->step_x == 1)
				calc_info->color = (info->texture)[N][TEX_HEIGHT * \
				calc_info->tex_y + calc_info->tex_x];
			else if (calc_info->side == 0 && calc_info->step_x == -1)
				calc_info->color = (info->texture)[S][TEX_HEIGHT * \
				calc_info->tex_y + calc_info->tex_x];
		}
		info->buffer[calc_info->y][calc_info->x] = calc_info->color;
		calc_info->y++;
	}
}

void	ceiling_casting(t_game_info *info, t_calc_info *calc_info)
{
	calc_info->y = 0;
	while (calc_info->y < calc_info->draw_start)
	{
		(info->buffer)[calc_info->y][calc_info->x] = info->ceiling_color;
		calc_info->y++;
	}
}
