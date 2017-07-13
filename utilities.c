/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-meur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 20:04:40 by tle-meur          #+#    #+#             */
/*   Updated: 2016/01/22 17:18:21 by tle-meur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "fdf.h"
#include "mlx.h"

t_3d	fdf_3d_ini(double x, double y, double z)
{
	t_3d	pt;

	pt.x = x;
	pt.y = y;
	pt.z = z;
	return (pt);
}

void	fdf_ini(t_fdf *e)
{
	e->mlx = NULL;
	e->win = NULL;
	e->img = NULL;
	e->buf = NULL;
	e->hig = 840;
	e->wid = 1280;
	e->end = 0;
	e->bit = 0;
	e->lin = 0;
	e->mic.col = FDF_COL_MIN;
	e->mac.col = FDF_COL_MAX;
	e->mia = INT_MAX;
	e->maa = INT_MIN;
	e->p = NULL;
	e->npw = 0;
	e->nph = 0;
	e->dx = 300.;
	e->dy = 300.;
}

int		fdf_quit(t_fdf *e)
{
	int	i;

	if (e->img)
		mlx_destroy_image(e->mlx, e->img);
	if (e->win)
		mlx_destroy_window(e->mlx, e->win);
	if (e->p)
	{
		i = 0;
		while (e->p[i])
			free(e->p[i++]);
		free(e->p);
	}
	exit(0);
	return (0);
}

void	my_lstdel(void *ptr, size_t size)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (((char **)ptr)[i])
		free(((char **)ptr)[i++]);
	free(ptr);
	(void)size;
}
