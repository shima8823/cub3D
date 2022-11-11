/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wmlx_xpm_file_to_image.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:38:34 by shima             #+#    #+#             */
/*   Updated: 2022/11/10 20:40:05 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/wrapper_mlx.h"

void	*wmlx_xpm_file_to_image(void *mlx_ptr, char *filename, int *width, int *height)
{
	void	*p;

	p = mlx_xpm_file_to_image(mlx_ptr, filename, width, height);
	if (!p)
	{
		perror("mlx_xpm_file_to_image");
		exit(EXIT_FAILURE);
	}
	return (p);
}
