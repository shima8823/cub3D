/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_calc_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:59:30 by mhida             #+#    #+#             */
/*   Updated: 2022/11/14 14:42:51 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_draw_start_and_end(t_calc_info*calc_info)
{
	calc_info->drawStart = -(calc_info->lineHeight) / 2 + screenHeight / 2;
	if (calc_info->drawStart < 0)
		calc_info->drawStart = 0;
	calc_info->drawEnd = calc_info->lineHeight / 2 + screenHeight / 2;
	if (calc_info->drawEnd >= screenHeight)
		calc_info->drawEnd = screenHeight;
}

void	set_perp_wall_dist(t_calc_info *calc_info)
{
	if (calc_info->side == 0)
		calc_info->perpWallDist = (calc_info->sideDistX - calc_info->deltaDistX);
	else
		calc_info->perpWallDist = (calc_info->sideDistY - calc_info->deltaDistY);
}

void	set_step_and_side_dist(t_game_info *info, t_calc_info *calc_info)
{
	if (calc_info->rayDirX < 0)
	{
		calc_info->stepX = -1;
		calc_info->sideDistX = \
			(info->posX - calc_info->mapX) * calc_info->deltaDistX;
	}
	else
	{
		calc_info->stepX = 1;
		calc_info->sideDistX = \
			(calc_info->mapX + 1.0 - info->posX) * calc_info->deltaDistX;
	}
	if (calc_info->rayDirY < 0)
	{
		calc_info->stepY = -1;
		calc_info->sideDistY = \
			(info->posY - calc_info->mapY) * calc_info->deltaDistY;
	}
	else
	{
		calc_info->stepY = 1;
		calc_info->sideDistY = \
			(calc_info->mapY + 1.0 - info->posY) * calc_info->deltaDistY;
	}
}

void	set_calc_info(t_game_info *info, t_calc_info *calc_info)
{
	calc_info->cameraX = 2 * calc_info->x / (double)screenWidth - 1;
	calc_info->rayDirX = info->dirX + info->planeX * calc_info->cameraX;
	calc_info->rayDirY = info->dirY + info->planeY * calc_info->cameraX;
	calc_info->mapX = (int)info->posX;
	calc_info->mapY = (int)info->posY;
	calc_info->deltaDistX = (calc_info->rayDirX == 0) \
		? 1e30 : fabs(1 / calc_info->rayDirX);
	calc_info->deltaDistY = (calc_info->rayDirY == 0) \
		? 1e30 : fabs(1 / calc_info->rayDirY);
	calc_info->hit = 0;
}
