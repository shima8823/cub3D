/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:18:23 by shima             #+#    #+#             */
/*   Updated: 2022/11/11 16:19:15 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	count_array(char **split_line);
void	read_file(t_game_info *info, char *path);
void	line_parse(t_game_info *info, t_file_parse *fp, char *line);
void	init_file_parse(t_file_parse *fp);

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
	printf("NO: [%s]\n", info->texture_path[0]);
	printf("SO: [%s]\n", info->texture_path[1]);
	printf("WE: [%s]\n", info->texture_path[2]);
	printf("EA: [%s]\n", info->texture_path[3]);
	printf("F: [%s]\n", info->floor_ceiling_color[0]);
	printf("C: [%s]\n", info->floor_ceiling_color[1]);
	close(fp.fd);
}

void	init_file_parse(t_file_parse *fp)
{
	fp->state = NEUTRAL;
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
	// skip_line
	if (ft_strlen(line) == 1 && ft_strchr(line, '\n'))
		return ;
	if (fp->state == NEUTRAL)
	{
		split_line = ft_split(line, ' ');
		if (count_array(split_line) != 2)
			error_exit(ERR_MSG_LINE_INFO_NUM);
		if (ft_strncmp(split_line[0], "NO", 3) == 0)
			fp->state = TEXTURE_MODE;
		else if (ft_strncmp(split_line[0], "F", 2) == 0)
			fp->state = COLOR_MODE;
		else
			error_exit(ERR_MSG_INVALID_ID);
	}
	if (fp->state == TEXTURE_MODE)
	{
		split_line = ft_split(line, ' ');
		if (count_array(split_line) != 2)
			error_exit(ERR_MSG_LINE_INFO_NUM);
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
			if (ft_strlen(line2) != 1 || !ft_strchr(line2, '\n'))
				error_exit(ERR_MSG_INVALID_ID);
		}
	}
	else if (fp->state == COLOR_MODE)
	{
		split_line = ft_split(line, ' ');
		if (count_array(split_line) != 2)
			error_exit(ERR_MSG_LINE_INFO_NUM);
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
			if (ft_strlen(line2) != 1 || !ft_strchr(line2, '\n'))
				error_exit(ERR_MSG_INVALID_ID);
		}
	}
	
}

int	count_array(char **split_line)
{
	int	i;

	i = 0;
	while (split_line[i])
		i++;
	return (i);
}
