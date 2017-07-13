/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-meur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 20:35:49 by tle-meur          #+#    #+#             */
/*   Updated: 2016/01/22 19:39:53 by tle-meur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include "fdf.h"
#include "libft/libft.h"

static int		read_color(char *s)
{
	int	i;
	int	c;
	int	size;
	int	color;

	if (*s == '0' && (s[1] == 'x' || s[1] == 'X'))
		s += 2;
	if ((size = ft_strlen(s)) > 6)
		return (-1);
	i = -1;
	color = 0;
	while (++i < size)
	{
		if (*s >= '0' && *s <= '9')
			c = *(s++) - '0';
		else if (*s >= 'a' && *s <= 'f')
			c = *(s++) - 'a' + 10;
		else if (*s >= 'A' && *s <= 'F')
			c = *(s++) - 'A' + 10;
		else
			return (-1);
		color += c * pow(16, (size - i));
	}
	return (color);
}

static t_list	*my_first_init(t_fdf *e, t_list **list, int *size)
{
	int		i;
	t_list	*tmp;

	e->nph = 0;
	tmp = *list;
	while (tmp)
	{
		i = 0;
		while (((char **)(tmp->content))[i])
			i++;
		e->npw = FT_MAX(e->npw, i);
		tmp = tmp->next;
		e->nph++;
	}
	if (!(e->p = (t_3d **)malloc((e->nph + 1) * sizeof(t_3d *))))
	{
		ft_lstdel(list, &my_lstdel);
		return (NULL);
	}
	i = 0;
	*size = e->nph;
	while (i <= *size)
		e->p[i++] = NULL;
	return (*list);
}

static int		check_list(t_fdf *e, t_list **list)
{
	int		i;
	int		j;
	t_list	*tmp;

	if (!(tmp = my_first_init(e, list, &i)))
		return (0);
	while ((j = -1) && tmp)
	{
		if (!(e->p[--i] = (t_3d *)malloc((e->npw + 1) * sizeof(t_3d))))
		{
			ft_lstdel(list, &my_lstdel);
			return (0);
		}
		while (((char **)tmp->content)[++j])
		{
			e->p[i][j].z = ft_atoi(((char **)tmp->content)[j]);
			e->mia = FT_MIN(e->mia, e->p[i][j].z);
			e->maa = FT_MAX(e->maa, e->p[i][j].z);
		}
		while (j < e->npw)
			e->p[i][j++].z = 0;
		tmp = tmp->next;
	}
	ft_lstdel(list, &my_lstdel);
	return (1);
}

static int		my_filllist(t_list **list, int fd)
{
	int		i;
	t_list	*tmp;
	char	**ret;
	char	*line;

	line = NULL;
	*list = NULL;
	while ((i = ft_gnl(fd, &line)) > 0)
	{
		ret = ft_strsplit(line, ' ');
		if (!(tmp = (t_list *)malloc(sizeof(t_list))))
		{
			ft_memdel((void **)&ret);
			ft_lstdel(list, &my_lstdel);
			return (-2);
		}
		tmp->content = ret;
		tmp->content_size = sizeof(char **);
		ft_lstadd(list, tmp);
	}
	ft_memdel((void **)&line);
	return (i);
}

int				my_parse(t_fdf *e, int ac, char **av)
{
	int		i;
	int		fd;
	t_list	*list;

	if ((fd = open(av[1], O_RDWR)) < 0 && ft_printf("fdf: %s: ", av[1]))
	{
		perror("");
		return (0);
	}
	if ((i = my_filllist(&list, fd)) == -2)
		return (0);
	if (close(fd) && ft_printf("fdf: %s: ", av[1]))
	{
		perror("");
		return (0);
	}
	if (!check_list(e, &list))
		return (0);
	if (i == -1 || ac < 3)
		return ((i == -1) ? 0 : 1);
	if ((e->mic.col = read_color(av[2])) < 0)
		return ((e->mic.col = FDF_COL_MIN) + 1);
	if ((ac < 4 || (e->mac.col = read_color(av[3])) < 0))
		return ((e->mac.col = e->mic.col) + 1);
	return (1);
}
