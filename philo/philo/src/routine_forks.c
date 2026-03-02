/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:00 by kyanagis          #+#    #+#             */
/*   Updated: 2026/01/11 00:00:00 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	fork_try_take(t_fork *fork)
{
	bool	ok;

	pthread_mutex_lock(&fork->mtx);
	ok = (fork->taken == false);
	if (ok)
		fork->taken = true;
	pthread_mutex_unlock(&fork->mtx);
	return (ok);
}

static void	fork_put(t_fork *fork)
{
	pthread_mutex_lock(&fork->mtx);
	fork->taken = false;
	pthread_mutex_unlock(&fork->mtx);
}

static bool	wait_for_second_fork(t_philo *ph)
{
	while (!should_stop(ph->box))
	{
		if (fork_try_take(ph->second))
			return (true);
		usleep(100);
	}
	return (false);
}

void	release_two_forks(t_philo *ph)
{
	fork_put(ph->second);
	fork_put(ph->first);
}

bool	take_two_forks(t_philo *ph, long long *out_start_us)
{
	while (!should_stop(ph->box))
	{
		if (!fork_try_take(ph->first))
		{
			if (!is_tight_even_cycle(&ph->box->cfg))
				usleep(100);
			continue ;
		}
		if (fork_try_take(ph->second)
			|| ((ph->box->cfg.philo_count % 2) != 0
				&& wait_for_second_fork(ph)))
		{
			*out_start_us = now_us();
			if (*out_start_us < 0)
				return (release_two_forks(ph), false);
			return (true);
		}
		fork_put(ph->first);
		if (!is_tight_even_cycle(&ph->box->cfg))
			usleep(100);
	}
	return (false);
}
