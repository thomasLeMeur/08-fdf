/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-meur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/15 06:05:50 by tle-meur          #+#    #+#             */
/*   Updated: 2016/01/31 15:20:16 by tle-meur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"
#include "libft/libft.h"

static int	my_col(t_fdf *e, double hight)
{
	double			percent;

	percent = (hight - e->mia) / (e->wia);
	return (round((e->mac.argb[2] - e->mic.argb[2]) * percent) * 65536 +
			round((e->mac.argb[1] - e->mic.argb[1]) * percent) * 256 +
			round((e->mac.argb[0] - e->mic.argb[0]) * percent) + e->mic.col);
}

static void	trace_line(t_fdf *e, t_3d *a, t_3d *b)
{
	t_3d	c;
	double	d;
	t_3d	deriv;
	int		offset;

	c = fdf_3d_ini(a->x, a->y, a->z);
	d = sqrt(pow(b->x - a->x, 2) + pow(b->y - a->y, 2));
	deriv = fdf_3d_ini((b->x - a->x) / d, (b->y - a->y) / d, (b->z - a->z) / d);
	while (d-- >= 0)
	{
		offset = (int)c.y * e->lin + (int)c.x * e->bit;
		if (offset < e->hig * e->wid * e->bit && offset >= 0)
			*(int *)(e->buf + offset) = my_col(e, c.z);
		c.x += deriv.x;
		c.y += deriv.y;
		c.z += deriv.z;
	}
}

static int	init_scales(t_fdf *e)
{
	if (!e->npw)
		return (0);
	if (e->npw == 1 && e->nph == 1)
	{
		*(int *)(e->buf + e->hig / 2 * e->lin + e->wid / 2 * e->bit) =
		my_col(e, e->p[0][0].z);
		return (0);
	}
	e->off = FT_MIN(e->wid, e->hig) / (double)FT_MIN(e->npw, e->nph);
	e->dx = FDF_SQRT2_2 * (-(e->nph - 1) * e->off) * -1;
	e->dy = FDF_SQRT_23_ * e->p[0][0].z;
	e->fx = e->wid / (FDF_SQRT2_2 * ((e->npw - 1) * e->off) + e->dx);
	e->fy = e->hig / (FDF_SQRT_23_ * -e->p[e->nph - 1][e->npw - 1].z +
	FDF_1_SQRT6 * ((e->npw - 1) * e->off + (e->nph - 1) * e->off) + e->dy);
	e->f = FT_MIN(e->fx, e->fy);
	if (e->fy < e->fx)
		e->dx += (e->wid - ((FDF_SQRT2_2 * ((e->npw - 1) * e->off) + e->dx) -
		e->dx * e->f)) / 2.;
	else
		e->dy += (e->hig - ((FDF_SQRT_23_ * -e->p[e->nph - 1][e->npw - 1].z +
		FDF_1_SQRT6 * ((e->npw - 1) * e->off + (e->nph - 1) * e->off) +
		e->dy) * e->f - (FDF_SQRT_23_ * -e->p[0][0].z + e->dy) * e->f)) / 2.;
	return (1);
}

void		prepare_image(t_fdf *e)
{
	int		i;
	int		j;
	int		size;
	t_3d	*v;
	t_3d	**vertexes;

	if (!init_scales(e))
		return ;
	i = -1;
	size = e->npw;
	vertexes = e->p;
	while ((v = vertexes[++i]))
	{
		j = -1;
		while (++j < size)
		{
			v[j].x = (FDF_SQRT2_2 * (j * e->off - i * e->off) + e->dx) * e->f;
			v[j].y = (FDF_SQRT_23_ * -v[j].z + FDF_1_SQRT6 * (j * e->off +
					i * e->off) + e->dy) * e->f;
			if (j)
				trace_line(e, &v[j - 1], &v[j]);
			if (i)
				trace_line(e, &vertexes[i - 1][j], &v[j]);
		}
	}
}
