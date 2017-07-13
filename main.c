/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-meur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 15:16:36 by tle-meur          #+#    #+#             */
/*   Updated: 2016/01/22 17:17:43 by tle-meur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include "libft/libft.h"

int	main(int ac, char **av)
{
	t_fdf	e;

	fdf_ini(&e);
	if (ac < 2 || !my_parse(&e, ac, av))
		return (0);
	e.wia = FT_MAX(e.maa - e.mia, 1);
	if (!(e.mlx = mlx_init()))
		return (fdf_quit(&e));
	if (!(e.win = mlx_new_window(e.mlx, e.wid, e.hig, "FdF")))
		return (fdf_quit(&e));
	if (!(e.img = mlx_new_image(e.mlx, e.wid, e.hig)))
		return (fdf_quit(&e));
	e.buf = mlx_get_data_addr(e.img, &e.bit, &e.lin, &e.end);
	e.bit /= 8;
	prepare_image(&e);
	mlx_key_hook(e.win, &my_key_func, &e);
	mlx_expose_hook(e.win, &my_expose_func, &e);
	mlx_loop(e.mlx);
	return (0);
}
