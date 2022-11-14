/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:10:45 by mhida             #+#    #+#             */
/*   Updated: 2022/11/15 00:32:35 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	init_minimap_info(t_game_info *info, t_minimap_info *mnmap_info)
{
	mnmap_info->y_begin = SCREEN_HEIGHT / 1.3;
	mnmap_info->y_end = SCREEN_HEIGHT - 1;
	mnmap_info->x_begin = SCREEN_WIDTH / 1.3;
	mnmap_info->x_begin_tmp = SCREEN_WIDTH / 1.3;
	mnmap_info->x_end = SCREEN_WIDTH - 1;
	mnmap_info->y = 0;
	mnmap_info->x = 0;
	mnmap_info->y_for_div = (mnmap_info->y_end / info->map_size_y) \
		- (mnmap_info->y_begin / info->map_size_y);
	mnmap_info->x_for_div = (mnmap_info->x_end / info->map_size_x) \
		- (mnmap_info->x_begin / info->map_size_x);
}

void	set_minimap(t_game_info *info)
{
	t_minimap_info	mnmap_info;

	init_minimap_info(info, &mnmap_info);
	while (mnmap_info.y_begin < mnmap_info.y_end)
	{
		mnmap_info.x = 0;
		while (mnmap_info.x_begin < mnmap_info.x_end)
		{
			if (info->map[mnmap_info.y][mnmap_info.x] == '1')
				info->buffer[mnmap_info.y_begin][mnmap_info.x_begin] = BLACK;
			else if ((int)info->pos_x == mnmap_info.y \
				&& (int)info->pos_y == mnmap_info.x)
				info->buffer[mnmap_info.y_begin][mnmap_info.x_begin] = RED;
			else if (info->map[mnmap_info.y][mnmap_info.x] == '0')
				info->buffer[mnmap_info.y_begin][mnmap_info.x_begin] = WHITE;
			mnmap_info.x_begin++;
			if (mnmap_info.x_begin % mnmap_info.x_for_div == 0)
				mnmap_info.x++;
		}
		mnmap_info.y_begin++;
		if (mnmap_info.y_begin % mnmap_info.y_for_div == 0)
			mnmap_info.y++;
		mnmap_info.x_begin = mnmap_info.x_begin_tmp;
	}
}
