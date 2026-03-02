/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:00:00 by kyanagis          #+#    #+#             */
/*   Updated: 2026/01/04 00:00:00 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_one(t_philo *ph, t_shared *box, long long now,
		bool *all_full)
{
	int			need;
	long long	die_us;
	long long	last_meal_us;
	int			meals_done;
	bool		dead;

	need = box->cfg.must_eat;
	die_us = (long long)box->cfg.die_ms * 1000;
	pthread_mutex_lock(&ph->meal_mutex);
	last_meal_us = ph->last_meal_us;
	meals_done = ph->meals_done;
	dead = (now - last_meal_us > die_us);
	pthread_mutex_unlock(&ph->meal_mutex);
	if (dead)
	{
		if (set_stop(box))
			print_death(box, now, ph->id);
		return (true);
	}
	if (need > 0 && meals_done < need)
		*all_full = false;
	return (false);
}

static bool	check_stop_conditions(t_philo *ph, t_shared *box)
{
	int			i;
	bool		all_full;
	long long	now;

	all_full = (box->cfg.must_eat > 0);
	now = now_us();
	i = 0;
	while (i < box->cfg.philo_count)
	{
		if (check_one(&ph[i], box, now, &all_full))
			return (true);
		i++;
	}
	if (all_full)
		(void)set_stop(box);
	return (all_full);
}

void	*monitor(void *arg)
{
	t_philo		*ph;
	t_shared	*box;

	ph = (t_philo *)arg;
	box = ph[0].box;
	if (!wait_for_start(box))
		return (NULL);
	while (!should_stop(box))
	{
		if (check_stop_conditions(ph, box))
			return (NULL);
		usleep(5000);
	}
	return (NULL);
}
