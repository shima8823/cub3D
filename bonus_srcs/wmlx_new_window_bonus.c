/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wmlx_new_window_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:19:36 by shima             #+#    #+#             */
/*   Updated: 2022/11/14 22:12:41 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wrapper_mlx.h"

void	*wmlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title)
{
	void	*p;

	p = mlx_new_window(mlx_ptr, size_x, size_y, title);
	if (!p)
	{
		perror("mlx_new_window");
		exit(EXIT_FAILURE);
	}
	return (p);
}
