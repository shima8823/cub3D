/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:42:07 by mhida             #+#    #+#             */
/*   Updated: 2022/11/14 16:11:30 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	error_and_exit(void)
{
	printf("Map invalid!\n");
	exit(EXIT_FAILURE);
}

static void	free_is_checked(bool **is_checked, int map_height)
{
	int	i;

	i = 0;
	while (i < map_height)
		free(is_checked[i++]);
	free(is_checked);
}

static bool	flood_fill_2(t_game_info *info, bool **is_checked, int x, int y)
{
	if (x >= info->map_size_x || y >= info->map_size_y || x < 0 || y < 0)
		return (false);
	if (is_checked[y][x] == true)
		return (true);
	if (info->map[y][x] == '1')
		return (true);
	else
		is_checked[y][x] = true;
	if (flood_fill_2(info, is_checked, x, y - 1) == false)
		return (false);
	if (flood_fill_2(info, is_checked, x - 1, y) == false)
		return (false);
	if (flood_fill_2(info, is_checked, x, y + 1) == false)
		return (false);
	if (flood_fill_2(info, is_checked, x + 1, y) == false)
		return (false);
	return (true);
}

static int	get_map_width_max(char map_str[MAX_Y][MAX_X], int map_height)
{
	int	i;
	int	max_width;
	int	width;

	i = 0;
	max_width = 0;
	while (i < map_height)
	{
		width = ft_strlen(map_str[i]);
		if (width > max_width)
			max_width = width;
		i++;
	}
	if (max_width <= 2)
		error_and_exit();
	return (max_width);
}

void	flood_fill(t_game_info *info)
{
	bool	**is_checked;
	int		i;

	if (info->map_size_y <= 2)
		error_and_exit();
	info->map_size_x = get_map_width_max(info->map, info->map_size_y);
	is_checked = (bool **)malloc(sizeof(bool *) * info->map_size_y);
	if (!is_checked)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < info->map_size_y)
	{
		is_checked[i] = (bool *)ft_calloc(sizeof(bool), info->map_size_x + 1);
		if (!is_checked[i])
			exit(EXIT_FAILURE);
		i++;
	}
	if (flood_fill_2(info, is_checked, \
		(int)info->pos_y, (int)info->pos_x) == false)
		error_and_exit();
	else
		printf("Map OK!\n");
	free_is_checked(is_checked, info->map_size_y);
}
