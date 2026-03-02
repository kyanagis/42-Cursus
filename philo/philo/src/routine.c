/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:00 by kyanagis          #+#    #+#             */
/*   Updated: 2026/01/11 00:00:00 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo		*ph;
	long long	end_eat_us;
	long long	sleep_end_us;

	ph = (t_philo *)arg;
	if (!wait_for_start(ph->box))
		return (NULL);
	if (ph->left == ph->right)
	{
		handle_single_philo(ph);
		return (NULL);
	}
	stagger_start(ph);
	while (!should_stop(ph->box))
	{
		if (!do_eat(ph, &end_eat_us))
			break ;
		print_state_at(ph->box, end_eat_us, ph->id, "is sleeping");
		sleep_end_us = calc_sleep_end_us(ph, end_eat_us);
		sleep_until(ph->box, sleep_end_us);
		think(ph, sleep_end_us);
	}
	return (NULL);
}
