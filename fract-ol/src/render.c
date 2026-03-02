/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:11:16 by kyanagis          #+#    #+#             */
/*   Updated: 2025/07/12 01:53:14 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx_err_msg.h"

static void	put_line(t_img *img, int *buf, int y)
{
	ft_memcpy(img->addr + y * img->line, buf, WIN_W * sizeof(int));
}

static int	render_pixel(t_fract *f, double cx, double cy)
{
	if (f->kind == MANDELBROT)
		return (get_color(iter_mandel(cx, cy, f), f->iter_base, f->hue));
	else if (f->kind == JULIA)
		return (get_color(iter_julia(cx, cy, f), f->iter_base, f->hue));
	else if (f->kind == BURNING_SHIP)
		return (get_color(iter_burning(cx, cy, f), f->iter_base, f->hue));
	else if (f->kind == SIERPINSKI)
	{
		if (sierpinski(cx, cy))
			return (0xFFFFFF);
		else
			return (0x000000);
	}
	return (0);
}

void	render_frame(t_fract *f)
{
	t_render_vars	v;
	int				line[WIN_W];
	double			cx_start;

	v.inc = 4.0 / WIN_W / f->zoom;
	v.cy = (-WIN_H / 2.0) * v.inc + f->off_y;
	cx_start = (-WIN_W / 2.0) * v.inc + f->off_x;
	v.y = 0;
	while (v.y < WIN_H)
	{
		v.cx = cx_start;
		v.x = 0;
		while (v.x < WIN_W)
		{
			line[v.x] = render_pixel(f, v.cx, v.cy);
			v.cx += v.inc;
			++v.x;
		}
		put_line(&f->img, line, v.y);
		v.cy += v.inc;
		++v.y;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img.img, 0, 0);
}
