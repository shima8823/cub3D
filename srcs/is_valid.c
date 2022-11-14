/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:16:33 by mhida             #+#    #+#             */
/*   Updated: 2022/11/14 16:40:10 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_valid(char *path)
{
	char	*s;

	s = ft_strrchr(path, '.');
	if (!s || ft_strncmp(s, ".cub", 5) != 0)
		return (true);
	return (false);
}
