/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:59:18 by mhida             #+#    #+#             */
/*   Updated: 2022/11/14 14:55:12 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	floor_casting(t_game_info *info, t_calc_info *calc_info)
{
	while (calc_info->y < screenHeight)
	{
		(info->buffer)[calc_info->y][calc_info->x] = info->floor_color;
		calc_info->y++;
	}
}

void	set_tex_color_to_buffer(t_game_info *info, t_calc_info *calc_info)
{
	while (calc_info->y < calc_info->drawEnd)
	{
		calc_info->texY = (int)calc_info->texPos & (texHeight - 1);
		calc_info->texPos += calc_info->step;
		calc_info->color = 0;
		if (calc_info->texNum == 1)
		{
			if (calc_info->side == 1 && calc_info->stepY == 1)
				calc_info->color = (info->texture)[W][texHeight * \
				calc_info->texY + calc_info->texX];
			else if (calc_info->side == 1 && calc_info->stepY == -1)
				calc_info->color = (info->texture)[E][texHeight * \
				calc_info->texY + calc_info->texX];
			else if (calc_info->side == 0 && calc_info->stepX == 1)
				calc_info->color = (info->texture)[N][texHeight * \
				calc_info->texY + calc_info->texX];
			else if (calc_info->side == 0 && calc_info->stepX == -1)
				calc_info->color = (info->texture)[S][texHeight * \
				calc_info->texY + calc_info->texX];
		}
		info->buffer[calc_info->y][calc_info->x] = calc_info->color;
		calc_info->y++;
	}
}

void	ceiling_casting(t_game_info *info, t_calc_info *calc_info)
{
	calc_info->y = 0;
	while (calc_info->y < calc_info->drawStart)
	{
		(info->buffer)[calc_info->y][calc_info->x] = info->ceiling_color;
		calc_info->y++;
	}
}
