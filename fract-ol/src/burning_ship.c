/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 07:33:34 by kyanagis          #+#    #+#             */
/*   Updated: 2025/07/13 01:34:21 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	burning_loop(t_pair c, double *zr, double *zi, int limit)
{
	int		i;
	double	temp;
	double	zr2;
	double	zi2;

	i = 0;
	while (i < limit)
	{
		zr2 = *zr * *zr;
		zi2 = *zi * *zi;
		if (zr2 + zi2 > 4.0)
			break ;
		temp = zr2 - zi2 + c.x;
		*zi = fabs(2.0 * *zr * *zi) + c.y;
		*zr = fabs(temp);
		i++;
	}
	return (i);
}

int	iter_burning(double cx, double cy, const t_fract *f)
{
	t_pair	c;
	double	zr;
	double	zi;
	int		i;

	c.x = cx;
	c.y = cy;
	zr = 0;
	zi = 0;
	i = burning_loop(c, &zr, &zi, f->iter_base);
	if (i == f->iter_base)
		return (f->iter_base);
	return (i + 1.0 - log(log(zr * zr + zi * zi)) / log(2.0));
}
