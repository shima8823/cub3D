/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:10:39 by mhida             #+#    #+#             */
/*   Updated: 2022/11/14 16:12:56 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	dda(t_game_info *info, t_calc_info *calc_info)
{
	while (calc_info->hit == 0)
	{
		if (calc_info->side_dist_x < calc_info->side_dist_y)
		{
			calc_info->side_dist_x += calc_info->delta_dist_x;
			calc_info->map_x += calc_info->step_x;
			calc_info->side = 0;
		}
		else
		{
			calc_info->side_dist_y += calc_info->delta_dist_y;
			calc_info->map_y += calc_info->step_y;
			calc_info->side = 1;
		}
		if (info->map[calc_info->map_x][calc_info->map_y] != '0')
			calc_info->hit = 1;
	}
}
