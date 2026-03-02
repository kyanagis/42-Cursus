/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:00:00 by kyanagis          #+#    #+#             */
/*   Updated: 2026/01/04 00:00:00 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_fork_order(t_philo *list)
{
	if (!list || !list->left || !list->right)
		return ;
	if ((list->id % 2) == 0)
	{
		list->first = list->right;
		list->second = list->left;
	}
	else
	{
		list->first = list->left;
		list->second = list->right;
	}
}

static void	assign_forks(t_philo *ph, t_fork *forks, int idx, int count)
{
	ph->left = &forks[idx];
	if (idx + 1 == count)
		ph->right = &forks[0];
	else
		ph->right = &forks[idx + 1];
	set_fork_order(ph);
}

bool	philos_init(t_philo **out_philo, t_shared *box, t_fork *forks)
{
	int		count;
	int		idx;
	t_philo	*list;

	idx = 0;
	if (!out_philo || !box || !forks)
		return (false);
	count = box->cfg.philo_count;
	list = malloc(sizeof(t_philo) * count);
	if (!list)
		return (false);
	while (idx < count)
	{
		list[idx].id = idx + 1;
		list[idx].box = box;
		assign_forks(&list[idx], forks, idx, count);
		list[idx].meal_mutex_init = false;
		++idx;
	}
	*out_philo = list;
	return (true);
}
