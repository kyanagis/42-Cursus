/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:00 by kyanagis          #+#    #+#             */
/*   Updated: 2026/01/11 00:00:00 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_tight_even_cycle(const t_config *cfg)
{
	int	margin_ms;

	if ((cfg->philo_count % 2) != 0)
		return (false);
	margin_ms = cfg->die_ms - (cfg->eat_ms + cfg->sleep_ms);
	return (margin_ms > 0 && margin_ms <= 2);
}

void	stagger_start(t_philo *ph)
{
	long long	target_us;

	if ((ph->id % 2) != 0)
		return ;
	target_us = ph->box->start_us + (long long)ph->box->cfg.eat_ms * 1000;
	if (is_tight_even_cycle(&ph->box->cfg)
		&& target_us - 2000 > ph->box->start_us)
		target_us -= 2000;
	sleep_until(ph->box, target_us);
}

long long	calc_sleep_end_us(t_philo *ph, long long end_eat_us)
{
	long long	sleep_end_us;

	sleep_end_us = end_eat_us + (long long)ph->box->cfg.sleep_ms * 1000;
	if (is_tight_even_cycle(&ph->box->cfg)
		&& sleep_end_us - 2000 > end_eat_us)
		sleep_end_us -= 2000;
	return (sleep_end_us);
}

void	think(t_philo *ph, long long think_start_us)
{
	long long	margin_ms;
	long long	think_ms;
	long long	think_end_us;

	if ((ph->box->cfg.philo_count % 2) == 0)
	{
		if (is_tight_even_cycle(&ph->box->cfg))
			return ;
		print_state_at(ph->box, think_start_us, ph->id, "is thinking");
		return ;
	}
	margin_ms = ph->box->cfg.die_ms
		- (ph->box->cfg.eat_ms + ph->box->cfg.sleep_ms);
	think_ms = margin_ms / 3;
	if (margin_ms > 0 && margin_ms <= 250)
		think_ms = margin_ms / 6;
	print_state_at(ph->box, think_start_us, ph->id, "is thinking");
	if (think_ms <= 0)
		return ;
	think_end_us = think_start_us + (long long)think_ms * 1000;
	sleep_until(ph->box, think_end_us);
}
