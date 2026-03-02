/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:00:00 by kyanagis          #+#    #+#             */
/*   Updated: 2026/01/04 00:00:00 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	forks_init(t_fork **out_forks, int count)
{
	int		i;
	t_fork	*forks;

	i = 0;
	if (!out_forks || count < 1)
		return (false);
	forks = malloc(sizeof(t_fork) * count);
	if (!forks)
		return (false);
	while (i < count)
	{
		forks[i].id = i;
		forks[i].taken = false;
		if (pthread_mutex_init(&forks[i].mtx, NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&forks[i].mtx);
			free(forks);
			return (false);
		}
		++i;
	}
	*out_forks = forks;
	return (true);
}
