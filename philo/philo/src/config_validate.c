/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:00:00 by kyanagis          #+#    #+#             */
/*   Updated: 2026/01/04 21:29:52 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	validate_config(const t_config *config)
{
	if (config->philo_count < 1)
		return (false);
	if (config->die_ms < 1 || config->eat_ms < 1 || config->sleep_ms < 1)
		return (false);
	if (!(config->must_eat == -1 || config->must_eat >= 1))
		return (false);
	return (true);
}
