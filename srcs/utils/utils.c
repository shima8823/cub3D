/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:28:55 by shima             #+#    #+#             */
/*   Updated: 2022/11/13 07:16:38 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
