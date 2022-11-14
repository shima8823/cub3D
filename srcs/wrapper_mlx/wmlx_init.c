/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wmlx_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:58:42 by shima             #+#    #+#             */
/*   Updated: 2022/11/14 16:46:57 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/wrapper_mlx.h"

void	*wmlx_init(void)
{
	void	*p;

	p = mlx_init();
	if (!p)
	{
		perror("mlx_init");
		exit(EXIT_FAILURE);
	}
	return (p);
}
