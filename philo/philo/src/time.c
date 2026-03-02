/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:00:00 by kyanagis          #+#    #+#             */
/*   Updated: 2026/01/04 00:00:00 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	now_us(void)
{
	struct timeval	tv;
	long long		sec_us;
	long long		usec;

	if (gettimeofday(&tv, NULL))
		return (-1);
	sec_us = (long long)tv.tv_sec * 1000000;
	usec = (long long)tv.tv_usec;
	return (sec_us + usec);
}

long long	now_ms(void)
{
	long long	us;

	us = now_us();
	if (us < 0)
		return (-1);
	return (us / 1000);
}
