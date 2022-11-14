/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:10:39 by mhida             #+#    #+#             */
/*   Updated: 2022/11/14 14:43:05 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	dda(t_game_info *info, t_calc_info *calc_info)
{
	while (calc_info->hit == 0)
	{
		if (calc_info->sideDistX < calc_info->sideDistY)
		{
			calc_info->sideDistX += calc_info->deltaDistX;
			calc_info->mapX += calc_info->stepX;
			calc_info->side = 0;
		}
		else
		{
			calc_info->sideDistY += calc_info->deltaDistY;
			calc_info->mapY += calc_info->stepY;
			calc_info->side = 1;
		}
		if (info->map[calc_info->mapX][calc_info->mapY] != '0')
			calc_info->hit = 1;
	}
}
