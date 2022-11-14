#include "../includes/cub3d.h"

void	set_minimap(t_game_info *info)
{
	int	y_begin = SCREEN_HEIGHT / 2;
	int	y_end = SCREEN_HEIGHT - 1;
	int	x_begin = SCREEN_WIDTH / 2;
	int	x_begin_tmp = SCREEN_WIDTH / 2;
	int	x_end = SCREEN_WIDTH - 1;
	int y = 0;
	int x = 0;
	int y_for_div = (SCREEN_HEIGHT / info->map_size_y) / 2;
	int x_for_div = (SCREEN_WIDTH / info->map_size_x) / 2;

	while (y_begin < y_end)
	{
		x = 0;
		while (x_begin < x_end)
		{
			if (info->map[y][x] == '1')
				info->buffer[y_begin][x_begin] = BLACK;
			else if ((int)info->pos_x == y && (int)info->pos_y == x)
				info->buffer[y_begin][x_begin] = RED;
			else
				info->buffer[y_begin][x_begin] = WHITE;
			x_begin++;
			if (x_begin % x_for_div == 0)
				x++;
		}
		y_begin++;
		if (y_begin % y_for_div == 0)
			y++;
		x_begin = x_begin_tmp;
	}
}
