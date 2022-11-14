/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:16:33 by mhida             #+#    #+#             */
/*   Updated: 2022/11/14 22:10:03 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

bool	is_valid(char *path)
{
	char	*s;

	s = ft_strrchr(path, '.');
	if (!s || ft_strncmp(s, ".cub", 5) != 0)
		return (true);
	return (false);
}
