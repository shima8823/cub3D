/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 21:14:56 by shima             #+#    #+#             */
/*   Updated: 2022/11/14 11:43:35 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static unsigned int	atoi_color(char *s);

unsigned int	get_color(char *line)
{
	char			**colors;
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;

	colors = ft_split(line, ',');
	if (count_array(colors) != 3)
		error_exit(ERR_MSG_INVALID_ID);
	red = atoi_color(colors[0]);
	green = atoi_color(colors[1]);
	blue = atoi_color(colors[2]);
	free(colors[0]);
	free(colors[1]);
	free(colors[2]);
	free(colors);
	return (red << 16 | green << 8 | blue);
}

static unsigned int	atoi_color(char *s)
{
	size_t			i;
	unsigned int	num;

	if (!s)
		exit(EXIT_FAILURE);
	i = 0;
	num = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			error_exit(ERR_MSG_COLOR_CHAR);
		num = num * 10 + s[i++] - '0';
	}
	if (i > 3 || num > 255)
		error_exit(ERR_MSG_COLOR_RANGE);
	return (num);
}
