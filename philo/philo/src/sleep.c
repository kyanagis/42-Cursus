/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:00:00 by kyanagis          #+#    #+#             */
/*   Updated: 2026/01/04 00:00:00 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long long	get_headroom_us(t_shared *box)
{
	long long	headroom_us;

	headroom_us = 200;
	if (is_tight_even_cycle(&box->cfg))
		headroom_us = 2000;
	return (headroom_us);
}

static useconds_t	calc_sleep_us(long long remaining_us, long long headroom_us)
{
	useconds_t	sleep_us;

	sleep_us = 0;
	if (remaining_us > headroom_us * 2)
		sleep_us = (useconds_t)(remaining_us / 2);
	if (sleep_us > 999999)
		sleep_us = 999999;
	return (sleep_us);
}

static void	spin_until(long long target_us)
{
	while (now_us() < target_us)
		;
}

void	sleep_until(t_shared *box, long long target_us)
{
	long long	now;
	long long	headroom_us;
	long long	remaining_us;
	useconds_t	sleep_us;

	headroom_us = get_headroom_us(box);
	while (!should_stop(box))
	{
		now = now_us();
		if (now >= target_us)
			return ;
		remaining_us = target_us - now;
		sleep_us = calc_sleep_us(remaining_us, headroom_us);
		if (sleep_us > 0)
			usleep(sleep_us);
		else
			spin_until(target_us);
	}
}
