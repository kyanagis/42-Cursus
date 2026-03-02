/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:52:29 by kyanagis          #+#    #+#             */
/*   Updated: 2025/07/05 04:52:19 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color_theme.h"
#include "fractol.h"

static int	compose_rgb(double prog, double brt, double sat, double phase)
{
	int	red;
	int	green;
	int	blue;

	red = (int)(HI * brt + 90.0 * sat * sin(6.0 * M_PI * prog + phase));
	green = (int)(HI * brt + 90.0 * sat * sin(6.0 * M_PI * prog + 2.0 + phase));
	blue = (int)(HI * brt + 90.0 * sat * sin(6.0 * M_PI * prog + 4.0 + phase));
	red &= 0xFF;
	green &= 0xFF;
	blue &= 0xFF;
	return ((red << 16) | (green << 8) | blue);
}

int	get_color(double mu, int limit, int hue_deg)
{
	double	prog;
	double	tex;
	double	brt;
	double	sat;
	double	phase;

	if (mu >= limit - 0.5)
		return (0x000000);
	prog = mu / (double)limit;
	tex = 0.5 + 0.5 * sin(TEX_FREQ * M_PI * mu);
	brt = BR_ADD + BR_GAIN * pow(prog, POW_EXP);
	brt *= 0.9 + TEX_BR_GAIN * tex;
	sat = SAT_BASE + SAT_GAIN * fabs(sin(M_PI * mu / STRIPE_P));
	sat *= 0.9 + TEX_SAT_GAIN * tex;
	phase = (hue_deg + 270.0 * prog * prog) * M_PI / 180.0;
	return (compose_rgb(prog, brt, sat, phase));
}
