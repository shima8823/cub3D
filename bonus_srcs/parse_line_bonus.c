/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:29:08 by shima             #+#    #+#             */
/*   Updated: 2022/11/14 22:11:32 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	parse_neutral(char *line, t_state_type *state);

void	parse_line(t_game_info *info, t_file_parse *fp, char *line)
{
	if (fp->skip_empty_line && is_empty_line(line))
	{
		return ;
	}
	if (fp->state == NEUTRAL)
	{
		parse_neutral(line, &fp->state);
	}
	if (fp->state == TEXTURE_MODE || fp->state == COLOR_MODE)
	{
		parse_texture_color(line, &info->texture_path, \
			&info->floor_ceiling_color, fp);
	}
	else if (fp->state == MAP_MODE)
	{
		parse_map(line, info, fp);
	}
}

bool	is_empty_line(char *line)
{
	if (!line)
		return (false);
	return (ft_strlen(line) == 1 && ft_strchr(line, '\n'));
}

static void	parse_neutral(char *line, t_state_type *state)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (count_array(split_line) != 2)
		error_exit(ERR_MSG_INVALID_ID);
	if (ft_strncmp(split_line[0], "NO", 3) == 0)
		*state = TEXTURE_MODE;
	else if (ft_strncmp(split_line[0], "F", 2) == 0)
		*state = COLOR_MODE;
	else
		error_exit(ERR_MSG_INVALID_ID);
	free(split_line[0]);
	free(split_line[1]);
	free(split_line);
}
