/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:58:17 by kyanagis          #+#    #+#             */
/*   Updated: 2025/06/16 21:58:18 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double	distance_est(double zr, double zi, double dr, double di)
{
	const double	mod = sqrt(zr * zr + zi * zi);

	return (mod * log(mod) / sqrt(dr * dr + di * di));
}

double	iter_julia(double zr, double zi, const t_fract *f)
{
	double	dr;
	double	di;
	int		i;
	double	tmp;

	dr = 1.0;
	di = 0.0;
	i = 0;
	while (zr * zr + zi * zi <= 4.0 && i < f->iter_base)
	{
		tmp = zr * zr - zi * zi + f->c_re;
		zi = 2.0 * zr * zi + f->c_im;
		zr = tmp;
		tmp = 2.0 * (zr * dr - zi * di);
		di = 2.0 * (zr * di + zi * dr);
		dr = tmp + 1.0;
		++i;
	}
	if (i == f->iter_base)
		return ((double)f->iter_base);
	return (i + 1.0 / (1.0 + distance_est(zr, zi, dr, di) * 10.0));
}
