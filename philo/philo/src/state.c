/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:00:00 by kyanagis          #+#    #+#             */
/*   Updated: 2026/01/05 19:09:14 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	should_stop(t_shared *box)
{
	bool	flag;

	pthread_mutex_lock(&box->state_mutex);
	flag = (box->stop != 0);
	pthread_mutex_unlock(&box->state_mutex);
	return (flag);
}

bool	wait_for_start(t_shared *box)
{
	int			started;
	int			stopping;
	long long	start_us;

	while (1)
	{
		pthread_mutex_lock(&box->state_mutex);
		started = (box->started != 0);
		stopping = (box->stop != 0);
		start_us = box->start_us;
		pthread_mutex_unlock(&box->state_mutex);
		if (stopping)
			return (false);
		if (started)
			break ;
		usleep(100);
	}
	sleep_until(box, start_us);
	return (!should_stop(box));
}

bool	set_stop(t_shared *box)
{
	bool	was_set;

	pthread_mutex_lock(&box->state_mutex);
	was_set = (box->stop != 0);
	if (!was_set)
		box->stop = 1;
	pthread_mutex_unlock(&box->state_mutex);
	return (!was_set);
}
