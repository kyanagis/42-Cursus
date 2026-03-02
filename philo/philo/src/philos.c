/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:00:00 by kyanagis          #+#    #+#             */
/*   Updated: 2026/01/04 00:00:00 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_start(t_philo *ph, t_shared *box)
{
	long long	start_us;
	int			i;
	int			count;

	start_us = now_us() + 10000;
	pthread_mutex_lock(&box->state_mutex);
	box->start_us = start_us;
	pthread_mutex_unlock(&box->state_mutex);
	count = box->cfg.philo_count;
	i = 0;
	while (i < count)
	{
		pthread_mutex_lock(&ph[i].meal_mutex);
		ph[i].last_meal_us = start_us;
		ph[i].meals_done = 0;
		pthread_mutex_unlock(&ph[i].meal_mutex);
		i++;
	}
	pthread_mutex_lock(&box->state_mutex);
	box->started = 1;
	pthread_mutex_unlock(&box->state_mutex);
}

static void	join_all(t_philo *ph, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(ph[i].thread, NULL);
		i++;
	}
}

static bool	start_one(t_philo *ph)
{
	if (pthread_mutex_init(&ph->meal_mutex, NULL) != 0)
		return (false);
	ph->meal_mutex_init = true;
	ph->last_meal_us = ph->box->start_us;
	ph->meals_done = 0;
	if (pthread_create(&ph->thread, NULL, philo_routine, ph) != 0)
	{
		pthread_mutex_destroy(&ph->meal_mutex);
		ph->meal_mutex_init = false;
		return (false);
	}
	return (true);
}

static bool	start_all_philos(t_philo *ph, t_shared *box)
{
	int	i;
	int	count;

	count = box->cfg.philo_count;
	i = 0;
	while (i < count)
	{
		if (!start_one(&ph[i]))
		{
			(void)set_stop(box);
			join_all(ph, i);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	philos_start(t_philo *ph, t_shared *box)
{
	pthread_t	monitor_thread;
	int			count;

	if (!ph || !box)
		return (false);
	count = box->cfg.philo_count;
	pthread_mutex_lock(&box->state_mutex);
	box->start_us = 0;
	box->started = 0;
	box->stop = 0;
	pthread_mutex_unlock(&box->state_mutex);
	if (!start_all_philos(ph, box))
		return (false);
	if (pthread_create(&monitor_thread, NULL, monitor, ph) != 0)
	{
		(void)set_stop(box);
		join_all(ph, count);
		return (false);
	}
	set_start(ph, box);
	pthread_join(monitor_thread, NULL);
	join_all(ph, count);
	return (true);
}
