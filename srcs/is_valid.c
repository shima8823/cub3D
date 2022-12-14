/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:16:33 by mhida             #+#    #+#             */
/*   Updated: 2022/11/14 20:00:42 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_valid(char *path)
{
	char	*s;

	s = ft_strrchr(path, '.');
	if (!s || ft_strncmp(s, ".cub", 5) != 0)
		return (false);
	return (true);
}
