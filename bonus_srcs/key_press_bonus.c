/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:28:04 by mhida             #+#    #+#             */
/*   Updated: 2022/11/14 22:10:17 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	key_press(int keycode, t_game_info *info)
{
	if (keycode == KEY_W)
		press_w(info);
	else if (keycode == KEY_S)
		press_s(info);
	else if (keycode == KEY_D)
		press_d(info);
	else if (keycode == KEY_A)
		press_a(info);
	else if (keycode == KEY_RIGHT_ARROW)
		press_right_arrow(info);
	else if (keycode == KEY_LEFT_ARROW)
		press_left_arrow(info);
	else if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
