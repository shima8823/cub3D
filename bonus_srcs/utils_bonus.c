/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:28:55 by shima             #+#    #+#             */
/*   Updated: 2022/11/14 22:12:08 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	error_exit(char *err_msg)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(err_msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	count_array(char **split_line)
{
	int	i;

	i = 0;
	while (split_line[i])
		i++;
	return (i);
}
