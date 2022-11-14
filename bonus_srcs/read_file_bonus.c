/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:18:23 by shima             #+#    #+#             */
/*   Updated: 2022/11/14 22:11:52 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	init_file_parse(t_file_parse *fp, char *path);
static void	validate_game_info(t_game_info *info, t_file_parse *fp);

void	read_file(t_game_info *info, char *path)
{
	t_file_parse	fp;
	char			*line;

	init_file_parse(&fp, path);
	while (true)
	{
		line = get_next_line(fp.fd);
		if (!line)
			break ;
		parse_line(info, &fp, line);
		free(line);
	}
	close(fp.fd);
	validate_game_info(info, &fp);
	info->floor_color = get_color(info->floor_ceiling_color[0]);
	info->ceiling_color = get_color(info->floor_ceiling_color[1]);
}

static void	init_file_parse(t_file_parse *fp, char *path)
{
	fp->fd = open(path, O_RDONLY);
	if (fp->fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
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

static void	validate_game_info(t_game_info *info, t_file_parse *fp)
{
	if (!info->texture_path[N]
		|| !info->texture_path[S]
		|| !info->texture_path[W]
		|| !info->texture_path[E]
		|| !info->floor_ceiling_color[0]
		|| !info->floor_ceiling_color[1]
		|| info->spawn_dir == 0
		|| fp->exists_nl_end_of_map)
		error_exit(ERR_MSG_INVALID_ID);
	flood_fill(info);
}
