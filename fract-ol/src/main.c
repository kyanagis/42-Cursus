/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 07:30:15 by kyanagis          #+#    #+#             */
/*   Updated: 2025/07/13 03:00:37 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	print_usage(void)
{
	ft_printf("Usage:\n");
	ft_printf("  ./fractol mandelbrot\n");
	ft_printf("  ./fractol julia <real> <imag>\n");
	ft_printf("  ./fractol burn\n");
	ft_printf("  ./fractol sier\n");
}

static int	is_number(const char *s)
{
	int	seen_digit;
	int	seen_dot;

	if (!s || !*s)
		return (0);
	if (*s == '+' || *s == '-')
		++s;
	seen_digit = 0;
	seen_dot = 0;
	while (*s)
	{
		if (*s == '.' && !seen_dot)
			seen_dot = 1;
		else if (*s >= '0' && *s <= '9')
			seen_digit = 1;
		else
			return (0);
		++s;
	}
	return (seen_digit);
}

static int	parse_julia(t_fract *f, int ac, char **av)
{
	f->kind = JULIA;
	if (ac == 4 && is_number(av[2]) && is_number(av[3]))
	{
		f->c_re = ft_atof(av[2]);
		f->c_im = ft_atof(av[3]);
		return (1);
	}
	else if (ac == 2)
	{
		f->c_re = -0.8;
		f->c_im = 0.156;
		return (1);
	}
	return (0);
}

static int	parse_args(t_fract *f, int ac, char **av)
{
	if (ac < 2)
	{
		print_usage();
		return (0);
	}
	if (ac == 2 && ft_strcmp(av[1], "mandelbrot") == 0)
	{
		f->kind = MANDELBROT;
		return (1);
	}
	else if ((ft_strcmp(av[1], "julia") == 0) && parse_julia(f, ac, av))
		return (1);
	else if (ft_strcmp(av[1], "burn") == 0)
	{
		f->kind = BURNING_SHIP;
		return (1);
	}
	else if (ft_strcmp(av[1], "sier") == 0)
	{
		f->kind = SIERPINSKI;
		return (1);
	}
	print_usage();
	return (0);
}

int	main(int ac, char **av)
{
	t_fract	f;

	ft_bzero(&f, sizeof(f));
	if (!parse_args(&f, ac, av))
		return (1);
	init_fract(&f);
	mlx_loop(f.mlx);
	return (0);
}
