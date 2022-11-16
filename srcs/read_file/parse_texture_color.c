/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:13:50 by shima             #+#    #+#             */
/*   Updated: 2022/11/16 21:48:38 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	parse_texture(char *(*texture_path)[4], \
			t_file_parse *fp, char **split_line);
static void	parse_color(char *(*floor_ceiling_color)[2], \
			t_file_parse *fp, char **split_line);

void	parse_texture_color(char *line, char *(*texture_path)[4], \
		char *(*floor_ceiling_color)[2], t_file_parse *fp)
{
	char	**split_line;

	fp->skip_empty_line = false;
	split_line = ft_split(line, ' ');
	if (count_array(split_line) != 2)
		error_exit(ERR_MSG_INVALID_ID);
	if (fp->state == TEXTURE_MODE)
		parse_texture(texture_path, fp, split_line);
	else
		parse_color(floor_ceiling_color, fp, split_line);
	free(split_line[0]);
	free(split_line);
}

static void	parse_texture(char *(*texture_path)[4], \
			t_file_parse *fp, char **split_line)
{
	char	*line;

	if (ft_strncmp(split_line[0], fp->texture_id[fp->texture_index], 3) == 0)
	{
		if ((*texture_path)[fp->texture_index])
			error_exit(ERR_MSG_INVALID_ID);
		split_line[1][ft_strlen(split_line[1]) - 1] = '\0';
		(*texture_path)[fp->texture_index] = split_line[1];
		fp->texture_index++;
	}
	else
		error_exit(ERR_MSG_INVALID_ID);
	if (fp->texture_index == 4)
	{
		if (fp->floor_ceiling_index == 0)
			fp->state = COLOR_MODE;
		else
			fp->state = MAP_MODE;
		line = get_next_line(fp->fd);
		if (!is_empty_line(line))
			error_exit(ERR_MSG_INVALID_ID);
		free(line);
		fp->skip_empty_line = true;
	}
}

static void	parse_color(char *(*floor_ceiling_color)[2], \
			t_file_parse *fp, char **split_line)
{
	char	*line;

	if (ft_strncmp(split_line[0], \
			fp->floor_ceiling_id[fp->floor_ceiling_index], 2) == 0)
	{
		if ((*floor_ceiling_color)[fp->floor_ceiling_index])
			error_exit(ERR_MSG_INVALID_ID);
		split_line[1][ft_strlen(split_line[1]) - 1] = '\0';
		(*floor_ceiling_color)[fp->floor_ceiling_index] = split_line[1];
		fp->floor_ceiling_index++;
	}
	else
		error_exit(ERR_MSG_INVALID_ID);
	if (fp->floor_ceiling_index == 2)
	{
		if (fp->texture_index == 0)
			fp->state = TEXTURE_MODE;
		else
			fp->state = MAP_MODE;
		line = get_next_line(fp->fd);
		if (!is_empty_line(line))
			error_exit(ERR_MSG_INVALID_ID);
		free(line);
		fp->skip_empty_line = true;
	}
}
