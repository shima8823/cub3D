/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wmlx_new_image_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:27:30 by shima             #+#    #+#             */
/*   Updated: 2022/11/14 22:12:37 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wrapper_mlx.h"

void	*wmlx_new_image(void *mlx_ptr, int width, int height)
{
	void	*p;

	p = mlx_new_image(mlx_ptr, width, height);
	if (!p)
	{
		perror("mlx_new_image");
		exit(EXIT_FAILURE);
	}
	return (p);
}
