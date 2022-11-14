/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_direction.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:36:30 by shima             #+#    #+#             */
/*   Updated: 2022/11/14 19:47:25 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_dir_info(double (*dir_info)[4][4]);
static void	set_player_dir(t_game_info *info, double *dir_info);

void	init_player_dir(t_game_info *info)
{
	char	c;
	double	dir_info[4][4];

	init_dir_info(&dir_info);
	c = info->spawn_dir;
	if (c == 'N')
		set_player_dir(info, dir_info[N]);
	else if (c == 'S')
		set_player_dir(info, dir_info[S]);
	else if (c == 'W')
		set_player_dir(info, dir_info[W]);
	else if (c == 'E')
		set_player_dir(info, dir_info[E]);
}

static void	init_dir_info(double (*dir_info)[4][4])
{
	(*dir_info)[N][DIR_X] = -1.0;
	(*dir_info)[N][DIR_Y] = 0.0;
	(*dir_info)[N][PLANE_X] = 0.0;
	(*dir_info)[N][PLANE_Y] = 0.66;
	(*dir_info)[S][DIR_X] = 1.0;
	(*dir_info)[S][DIR_Y] = 0.0;
	(*dir_info)[S][PLANE_X] = 0.0;
	(*dir_info)[S][PLANE_Y] = -0.66;
	(*dir_info)[W][DIR_X] = 0.0;
	(*dir_info)[W][DIR_Y] = -1.0;
	(*dir_info)[W][PLANE_X] = -0.66;
	(*dir_info)[W][PLANE_Y] = 0.0;
	(*dir_info)[E][DIR_X] = 0.0;
	(*dir_info)[E][DIR_Y] = 1.0;
	(*dir_info)[E][PLANE_X] = 0.66;
	(*dir_info)[E][PLANE_Y] = 0.0;
}

static void	set_player_dir(t_game_info *info, double *dir_info)
{
	info->dir_x = dir_info[DIR_X];
	info->dir_y = dir_info[DIR_Y];
	info->plane_x = dir_info[PLANE_X];
	info->plane_y = dir_info[PLANE_Y];
}
