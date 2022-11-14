/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_calc_info_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:59:30 by mhida             #+#    #+#             */
/*   Updated: 2022/11/14 14:42:56 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_step_and_tex_pos(t_calc_info *calc_info)
{
	calc_info->step = 1.0 * texHeight / calc_info->lineHeight;
	calc_info->texPos = (calc_info->drawStart - screenHeight / 2 \
		+ calc_info->lineHeight / 2) * calc_info->step;
}

void	set_tex_x_coordinate(t_calc_info *calc_info)
{
	calc_info->texX = (int)(calc_info->wallX * (double)texWidth);
	if (calc_info->side == 0 && calc_info->rayDirX > 0)
		calc_info->texX = texWidth - calc_info->texX - 1;
	if (calc_info->side == 1 && calc_info->rayDirY < 0)
		calc_info->texX = texWidth - calc_info->texX - 1;
}

void	set_wall_x(t_game_info *info, t_calc_info *calc_info)
{
	if (calc_info->side == 0)
		calc_info->wallX = info->posY + calc_info->perpWallDist * calc_info->rayDirY;
	else
		calc_info->wallX = info->posX + calc_info->perpWallDist * calc_info->rayDirX;
	calc_info->wallX -= floor(calc_info->wallX);
}

void	set_tex_num(t_game_info *info, t_calc_info*calc_info)
{
	calc_info->texNum = info->map[calc_info->mapX][calc_info->mapY] - '0';
	if (!(calc_info->texNum == 1 || calc_info->texNum == 0))
		calc_info->texNum = 0;
}
