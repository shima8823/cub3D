/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:18:23 by shima             #+#    #+#             */
/*   Updated: 2022/11/13 13:06:15 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	read_file(t_game_info *info, char *path);
void	line_parse(t_game_info *info, t_file_parse *fp, char *line);
void	init_file_parse(t_file_parse *fp);
bool	is_empty_line(char *line);
void	set_player_dir(t_game_info *info, double *dir_info);
void	init_dir_info(double (*dir_info)[4][4]);

void	read_file(t_game_info *info, char *path)
{
	t_file_parse fp;
	char	*line;

	init_file_parse(&fp);
	fp.fd = open(path, O_RDONLY);
	if (fp.fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	while (true)
	{
		line = get_next_line(fp.fd);
		if (!line)
			break;
		line_parse(info, &fp, line);
		free(line);
	}
	close(fp.fd);

	if (!info->texture_path[N]
		|| !info->texture_path[S]
		|| !info->texture_path[W]
		|| !info->texture_path[E]
		|| !info->floor_ceiling_color[0]
		|| !info->floor_ceiling_color[1]
		|| info->spawn_dir == 0
		|| fp.exists_nl_end_of_map)
		error_exit(ERR_MSG_INVALID_ID);
	info->floor_color = get_color(info->floor_ceiling_color[0]);
	info->ceiling_color = get_color(info->floor_ceiling_color[1]);
	printf("NO: [%s]\n", info->texture_path[N]);
	printf("SO: [%s]\n", info->texture_path[S]);
	printf("WE: [%s]\n", info->texture_path[W]);
	printf("EA: [%s]\n", info->texture_path[E]);
	printf("F: [%s]\n", info->floor_ceiling_color[0]);
	printf("C: [%s]\n", info->floor_ceiling_color[1]);
	printf("pos: %f %f\n", info->posX, info->posY);
	printf("spawn_dir: %c\n", info->spawn_dir);
}

void	init_file_parse(t_file_parse *fp)
{
	fp->state = NEUTRAL;
	fp->skip_empty_line = false;
	fp->exists_nl_end_of_map = true;
	fp->texture_index = 0;
	fp->floor_ceiling_index = 0;
	ft_strlcpy(fp->texture_id[0], "NO", 3);
	ft_strlcpy(fp->texture_id[1], "SO", 3);
	ft_strlcpy(fp->texture_id[2], "WE", 3);
	ft_strlcpy(fp->texture_id[3], "EA", 3);
	ft_strlcpy(fp->floor_ceiling_id[0], "F", 2);
	ft_strlcpy(fp->floor_ceiling_id[1], "C", 2);
}

void	line_parse(t_game_info *info, t_file_parse *fp, char *line)
{
	char	**split_line;
	char	*line2;

	if (fp->skip_empty_line && is_empty_line(line))
		return ;
	if (fp->state == NEUTRAL)
	{
		split_line = ft_split(line, ' ');
		if (count_array(split_line) != 2)
			error_exit(ERR_MSG_INVALID_ID);
		if (ft_strncmp(split_line[0], "NO", 3) == 0)
			fp->state = TEXTURE_MODE;
		else if (ft_strncmp(split_line[0], "F", 2) == 0)
			fp->state = COLOR_MODE;
		else
			error_exit(ERR_MSG_INVALID_ID);
	}
	if (fp->state == TEXTURE_MODE)
	{
		fp->skip_empty_line = false;
		split_line = ft_split(line, ' ');
		if (count_array(split_line) != 2)
			error_exit(ERR_MSG_INVALID_ID);
		if (ft_strncmp(split_line[0], fp->texture_id[fp->texture_index], 3) == 0)
		{
			if (info->texture_path[fp->texture_index])
				error_exit(ERR_MSG_INVALID_ID);
			split_line[1][ft_strlen(split_line[1]) - 1] = '\0';
			info->texture_path[fp->texture_index] = split_line[1];
			fp->texture_index++;
		}
		else
			error_exit(ERR_MSG_INVALID_ID);
		free(split_line[0]);
		free(split_line);
		if (fp->texture_index == 4)
		{
			// すでにflorだったらmapmode そうでなかったらflormode
			if (fp->floor_ceiling_index == 0)
				fp->state = COLOR_MODE;
			else
				fp->state = MAP_MODE;
			line2 = get_next_line(fp->fd);
			if (!is_empty_line(line2))
				error_exit(ERR_MSG_INVALID_ID);
			fp->skip_empty_line = true;
		}
	}
	else if (fp->state == COLOR_MODE)
	{
		fp->skip_empty_line = false;
		split_line = ft_split(line, ' ');
		if (count_array(split_line) != 2)
			error_exit(ERR_MSG_INVALID_ID);
		if (ft_strncmp(split_line[0], fp->floor_ceiling_id[fp->floor_ceiling_index], 2) == 0)
		{
			if (info->floor_ceiling_color[fp->floor_ceiling_index])
				error_exit(ERR_MSG_INVALID_ID);
			split_line[1][ft_strlen(split_line[1]) - 1] = '\0';
			info->floor_ceiling_color[fp->floor_ceiling_index] = split_line[1];
			fp->floor_ceiling_index++;
		}
		else
			error_exit(ERR_MSG_INVALID_ID);
		free(split_line[0]);
		free(split_line);
		if (fp->floor_ceiling_index == 2)
		{
			// すでにflorだったらmapmode そうでなかったらflormode
			if (fp->texture_index == 0)
				fp->state = TEXTURE_MODE;
			else
				fp->state = MAP_MODE;
			line2 = get_next_line(fp->fd);
			if (!is_empty_line(line2))
				error_exit(ERR_MSG_INVALID_ID);
			fp->skip_empty_line = true;
		}
	}
	else if (fp->state == MAP_MODE)
	{
		size_t	i;

		fp->skip_empty_line = false;
		if (is_empty_line(line))
			error_exit(ERR_MSG_INVALID_ID);
		if (!ft_strchr(line, '\n'))
			fp->exists_nl_end_of_map = false;
		i = 0;
		while (line[i])
		{
			if (!ft_strchr(" 01NSEW\n", line[i]))
				error_exit(ERR_MSG_INVALID_CHAR);
			if (ft_strchr("NSEW", line[i]))
			{
				if (info->spawn_dir != 0)
					error_exit(ERR_MSG_MULTIPLE_SPAWN);
				info->spawn_dir = line[i];
				info->posY = i;
				info->posX = info->map_size_y;
				line[i] = '0';
			}
			else if (line[i] == '\n')
			{
				line[i] = '\0';
				break ;
			}
			i++;
		}
		ft_strlcpy(info->map[info->map_size_y], line, MAP_X_LIMIT);
		info->map_size_y++;
		if (i - 1 > MAP_X_LIMIT - 1 || info->map_size_y - 1> MAP_Y_LIMIT - 1)
			error_exit(ERR_MSG_MAP_SIZE);
	}
}

bool	is_empty_line(char *line)
{
	if (!line)
		return (false);
	return (ft_strlen(line) == 1 && ft_strchr(line, '\n'));
}

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

void	init_dir_info(double (*dir_info)[4][4])
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

void	set_player_dir(t_game_info *info, double *dir_info)
{
	info->dirX = dir_info[DIR_X];
	info->dirY = dir_info[DIR_Y];
	info->planeX = dir_info[PLANE_X];
	info->planeY = dir_info[PLANE_Y];
}
