/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:00:00 by kyanagis          #+#    #+#             */
/*   Updated: 2026/01/04 00:00:00 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	shared_init(t_shared *box, t_config *config)
{
	if (!box || !config)
		return (false);
	box->cfg = *config;
	box->start_us = 0;
	box->started = 0;
	box->stop = 0;
	if (pthread_mutex_init(&box->print_mutex, NULL))
		return (false);
	if (pthread_mutex_init(&box->state_mutex, NULL))
	{
		pthread_mutex_destroy(&box->print_mutex);
		return (false);
	}
	return (true);
}
