/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-meur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 18:18:04 by tle-meur          #+#    #+#             */
/*   Updated: 2016/01/22 17:25:17 by tle-meur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <sys/types.h>

# define FDF_COL_MIN	0xff
# define FDF_COL_MAX	0xff00
# define FDF_ESC		53
# define FDF_SQRT2_2	0.7071067811865475727373109293694142252207
# define FDF_1_SQRT6	0.4082482904638630727411907628265907987952
# define FDF_SQRT_23_	0.8164965809277260344600790631375275552273

typedef struct	s_3d
{
	double	x;
	double	y;
	double	z;
}				t_3d;

typedef union	u_col
{
	int				col;
	unsigned char	argb[4];
}				t_col;

typedef struct	s_fdf
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*buf;
	int		hig;
	int		wid;
	int		end;
	int		bit;
	int		lin;
	t_col	mic;
	t_col	mac;
	int		mia;
	int		maa;
	int		wia;
	t_3d	**p;
	int		npw;
	int		nph;
	double	dx;
	double	dy;
	double	fx;
	double	fy;
	double	f;
	double	off;
}				t_fdf;

/*
**	parse.c
*/
int				my_parse(t_fdf *e, int ac, char **av);

/*
**	utilities.c
*/
void			fdf_ini(t_fdf *e);
int				fdf_quit(t_fdf *e);
void			my_lstdel(void *ptr, size_t size);
t_3d			fdf_3d_ini(double x, double y, double z);

/*
**	image.c
*/
void			prepare_image(t_fdf *e);

/*
**	functions.c
*/
int				my_expose_func(void *param);
int				my_key_func(int keycode, void *param);

#endif
