/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_mlx.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:59:37 by shima             #+#    #+#             */
/*   Updated: 2022/11/14 16:49:11 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAPPER_MLX_H
# define WRAPPER_MLX_H

# include <stdio.h>
# include <stdlib.h>
# include "../minilibx-linux/mlx.h"

char	*wmlx_get_data_addr(void *img_ptr, int *bits_per_pixel, \
	int *size_line, int *endian);
void	*wmlx_init(void);
void	*wmlx_new_image(void *mlx_ptr, int width, int height);
void	*wmlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);
void	*wmlx_xpm_file_to_image(void *mlx_ptr, char *filename, \
	int *width, int *height);

#endif
