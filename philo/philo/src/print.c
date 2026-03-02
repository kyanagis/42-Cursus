/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:00 by kyanagis          #+#    #+#             */
/*   Updated: 2026/01/11 00:00:00 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state_at(t_shared *box, long long timestamp_us, int id,
		const char *msg)
{
	long long	start_us;
	long long	elapsed_ms;

	pthread_mutex_lock(&box->print_mutex);
	pthread_mutex_lock(&box->state_mutex);
	if (box->stop != 0)
	{
		pthread_mutex_unlock(&box->state_mutex);
		pthread_mutex_unlock(&box->print_mutex);
		return ;
	}
	start_us = box->start_us;
	pthread_mutex_unlock(&box->state_mutex);
	elapsed_ms = (timestamp_us - start_us) / 1000;
	printf("%lld %d %s\n", elapsed_ms, id, msg);
	pthread_mutex_unlock(&box->print_mutex);
}

void	print_death(t_shared *box, long long timestamp_us, int id)
{
	long long	start_us;
	long long	elapsed_ms;

	pthread_mutex_lock(&box->print_mutex);
	pthread_mutex_lock(&box->state_mutex);
	start_us = box->start_us;
	pthread_mutex_unlock(&box->state_mutex);
	elapsed_ms = (timestamp_us - start_us) / 1000;
	printf("%lld %d died\n", elapsed_ms, id);
	pthread_mutex_unlock(&box->print_mutex);
}

void	print_state(t_shared *box, int id, const char *msg)
{
	long long	timestamp_us;

	timestamp_us = now_us();
	if (timestamp_us < 0)
		return ;
	print_state_at(box, timestamp_us, id, msg);
}
