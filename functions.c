/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-meur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/15 01:41:10 by tle-meur          #+#    #+#             */
/*   Updated: 2016/01/22 17:13:14 by tle-meur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int				my_expose_func(void *param)
{
	mlx_put_image_to_window(((t_fdf *)(param))->mlx, ((t_fdf *)(param))->win,
	((t_fdf *)(param))->img, 0, 0);
	return (1);
}

int				my_key_func(int key, void *param)
{
	if (key == FDF_ESC)
		fdf_quit(param);
	return (1);
}
