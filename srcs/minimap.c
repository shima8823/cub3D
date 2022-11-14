#include "../includes/cub3d.h"

void	set_minimap(t_game_info *info)
{
	int	y_begin = screenHeight / 2;
	int	y_end = screenHeight - 1;
	int	x_begin = screenWidth / 2;
	int	x_begin_tmp = screenWidth / 2;
	int	x_end = screenWidth - 1;
	int y = 0;
	int x = 0;
	int y_for_div = (screenHeight / mapHeight) / 2; // 480 / 24 / 2
	int x_for_div = (screenWidth / mapWidth) / 2; // 640 / 24 / 2

	while (y_begin < y_end)
	{
		x = 0;
		while (x_begin < x_end)
		{
			if (info->map[y][x] == '1')
				info->buffer[y_begin][x_begin] = 0; // black for 1
			else if ((int)info->posX == x && (int)info->posY == y)
				info->buffer[y_begin][x_begin] = 16711680; // red for player
			else
				info->buffer[y_begin][x_begin] = 16777215; // white for 0
			if (x_begin % x_for_div == 0)
				x++;
			x_begin++;
		}
		if (y_begin % y_for_div == 0)
			y++;
		y_begin++;
		x_begin = x_begin_tmp;
	}

	// y_begin = screenHeight / 1.5;
	// x_begin = screenWidth / 1.5;
	// while (y_begin < y_end)
	// {
	// 	while (x_begin < x_end)
	// 	{
	// 		info->buffer
	// 	}
	// }
}
