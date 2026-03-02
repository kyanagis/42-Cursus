/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_eat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:00 by kyanagis          #+#    #+#             */
/*   Updated: 2026/01/11 00:00:00 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	update_last_meal(t_philo *ph, long long start_us)
{
	long long	die_us;
	bool		dead;

	die_us = (long long)ph->box->cfg.die_ms * 1000;
	pthread_mutex_lock(&ph->meal_mutex);
	dead = (start_us - ph->last_meal_us > die_us);
	if (!dead)
		ph->last_meal_us = start_us;
	pthread_mutex_unlock(&ph->meal_mutex);
	if (!dead)
		return (true);
	if (set_stop(ph->box))
		print_death(ph->box, start_us, ph->id);
	return (false);
}

static long long	calc_eat_end(t_philo *ph, long long start_us)
{
	long long	end_us;

	end_us = start_us + (long long)ph->box->cfg.eat_ms * 1000;
	if (is_tight_even_cycle(&ph->box->cfg) && end_us - 2000 > start_us)
		end_us -= 2000;
	return (end_us);
}

static void	increment_meals_done(t_philo *ph)
{
	pthread_mutex_lock(&ph->meal_mutex);
	ph->meals_done += 1;
	pthread_mutex_unlock(&ph->meal_mutex);
}

bool	do_eat(t_philo *ph, long long *out_end_us)
{
	long long	start_us;
	long long	end_us;

	if (!take_two_forks(ph, &start_us))
		return (false);
	if (!update_last_meal(ph, start_us))
	{
		release_two_forks(ph);
		return (false);
	}
	print_state_at(ph->box, start_us, ph->id, "has taken a fork");
	print_state_at(ph->box, start_us, ph->id, "has taken a fork");
	print_state_at(ph->box, start_us, ph->id, "is eating");
	end_us = calc_eat_end(ph, start_us);
	sleep_until(ph->box, end_us);
	release_two_forks(ph);
	increment_meals_done(ph);
	if (out_end_us)
		*out_end_us = end_us;
	return (true);
}
