/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:13:33 by shima             #+#    #+#             */
/*   Updated: 2022/11/14 19:15:30 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	parse_map_row(char *line, t_game_info *info, size_t *x);

void	parse_map(char *line, t_game_info *info, t_file_parse *fp)
{
	size_t	x;

	fp->skip_empty_line = false;
	if (is_empty_line(line))
		error_exit(ERR_MSG_INVALID_ID);
	if (!ft_strchr(line, '\n'))
		fp->exists_nl_end_of_map = false;
	x = 0;
	parse_map_row(line, info, &x);
	ft_strlcpy(info->map[info->map_size_y], line, MAX_X);
	info->map_size_y++;
	if (x > MAX_X - 1 || info->map_size_y > MAX_Y - 1)
		error_exit(ERR_MSG_MAP_SIZE);
}

static void	parse_map_row(char *line, t_game_info *info, size_t *x)
{
	while (line[*x])
	{
		if (!ft_strchr(" 01NSEW\n", line[*x]))
			error_exit(ERR_MSG_INVALID_CHAR);
		if (ft_strchr("NSEW", line[*x]))
		{
			if (info->spawn_dir != 0)
				error_exit(ERR_MSG_MULTIPLE_SPAWN);
			info->spawn_dir = line[*x];
			info->posY = *x;
			info->posX = info->map_size_y;
			line[*x] = '0';
		}
		else if (line[*x] == ' ')
			line[*x] = '0';
		else if (line[*x] == '\n')
		{
			line[*x] = '\0';
			break ;
		}
		(*x)++;
	}
}
