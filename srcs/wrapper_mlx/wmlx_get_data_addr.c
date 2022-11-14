/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wmlx_get_data_addr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:35:05 by shima             #+#    #+#             */
/*   Updated: 2022/11/14 16:46:07 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/wrapper_mlx.h"

char	*wmlx_get_data_addr(void *img_ptr, int *bits_per_pixel, \
	int *size_line, int *endian)
{
	void	*p;

	p = mlx_get_data_addr(img_ptr, bits_per_pixel, size_line, endian);
	if (!p)
	{
		perror("mlx_get_data_addr");
		exit(EXIT_FAILURE);
	}
	return (p);
}
