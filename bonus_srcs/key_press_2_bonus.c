/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:35:16 by mhida             #+#    #+#             */
/*   Updated: 2022/11/14 22:10:08 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	press_a(t_game_info *info)
{
	if (info->map[(int)(info->pos_x)][(int)(info->pos_y - \
		-(info->dir_x) * info->move_speed)] == '0')
		info->pos_y -= -(info->dir_x) * info->move_speed;
	if (info->map[(int)(info->pos_x - \
		info->dir_y * info->move_speed)][(int)(info->pos_y)] == '0')
		info->pos_x -= info->dir_y * info->move_speed;
}

void	press_d(t_game_info *info)
{
	if (info->map[(int)(info->pos_x)][(int)(info->pos_y + \
		-(info->dir_x) * info->move_speed)] == '0')
		info->pos_y += -(info->dir_x) * info->move_speed;
	if (info->map[(int)(info->pos_x + \
		info->dir_y * info->move_speed)][(int)(info->pos_y)] == '0')
		info->pos_x += info->dir_y * info->move_speed;
}

void	press_s(t_game_info *info)
{
	if (info->map[(int)(info->pos_x - \
		info->dir_x * info->move_speed)][(int)info->pos_y] == '0')
		info->pos_x -= info->dir_x * info->move_speed;
	if (info->map[(int)info->pos_x][(int)(info->pos_y - \
		info->dir_y * info->move_speed)] == '0')
		info->pos_y -= info->dir_y * info->move_speed;
}

void	press_w(t_game_info *info)
{
	if (info->map[(int)(info->pos_x + \
		info->dir_x * info->move_speed)][(int)info->pos_y] == '0')
		info->pos_x += info->dir_x * info->move_speed;
	if (info->map[(int)info->pos_x][(int)(info->pos_y + \
		info->dir_y * info->move_speed)] == '0')
		info->pos_y += info->dir_y * info->move_speed;
}
