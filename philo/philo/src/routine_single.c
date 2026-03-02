/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 00:00:00 by kyanagis          #+#    #+#             */
/*   Updated: 2026/01/12 00:00:00 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_single_philo(t_philo *ph)
{
	long long	limit_us;

	pthread_mutex_lock(&ph->first->mtx);
	if (ph->first->taken)
	{
		pthread_mutex_unlock(&ph->first->mtx);
		return ;
	}
	ph->first->taken = true;
	pthread_mutex_unlock(&ph->first->mtx);
	print_state(ph->box, ph->id, "has taken a fork");
	limit_us = ph->box->start_us + (long long)ph->box->cfg.die_ms * 1000;
	sleep_until(ph->box, limit_us);
	pthread_mutex_lock(&ph->first->mtx);
	ph->first->taken = false;
	pthread_mutex_unlock(&ph->first->mtx);
}
