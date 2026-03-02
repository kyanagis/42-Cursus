/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:11:44 by kyanagis          #+#    #+#             */
/*   Updated: 2025/07/13 03:00:16 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx_err_msg.h"

static void	destroy_mlx(t_fract *f)
{
	if (f && f->img.img)
		mlx_destroy_image(f->mlx, f->img.img);
	if (f && f->win)
		mlx_destroy_window(f->mlx, f->win);
	if (f && f->mlx)
	{
		mlx_destroy_display(f->mlx);
		free(f->mlx);
	}
}

static void	panic(const char *msg, t_fract *f)
{
	ft_putendl_fd((char *)msg, STDERR_FILENO);
	destroy_mlx(f);
	exit(EXIT_FAILURE);
}

int	close_win(t_fract *f)
{
	destroy_mlx(f);
	exit(EXIT_SUCCESS);
	return (0);
}

void	init_fract(t_fract *f)
{
	f->mlx = mlx_init();
	if (!f->mlx)
		panic(ERR_MLX_INIT, f);
	f->win = mlx_new_window(f->mlx, WIN_W, WIN_H, "fractol");
	if (!f->win)
		panic(ERR_MLX_NEW_WINDOW, f);
	f->img.img = mlx_new_image(f->mlx, WIN_W, WIN_H);
	if (!f->img.img)
		panic(ERR_MLX_NEW_IMAGE, f);
	f->img.addr = mlx_get_data_addr(f->img.img, &f->img.bpp, &f->img.line,
			&f->img.endian);
	if (!f->img.addr)
		panic(ERR_MLX_ADDR, f);
	f->zoom = 1.0;
	f->iter_base = 40;
	f->hue = 0;
	render_frame(f);
	mlx_hook(f->win, 17, 0, close_win, f);
	mlx_key_hook(f->win, key_hook, f);
	mlx_mouse_hook(f->win, mouse_hook, f);
}
