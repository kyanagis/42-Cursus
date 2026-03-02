/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:24:49 by kyanagis          #+#    #+#             */
/*   Updated: 2026/01/04 21:38:14 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define ERR_PARSE_MSG "parse:error"
#define ERR_VALID_MSG "validate:error"
#define ERR_FORKS_MSG "forks:error"

static void	cleanup_philo_mutexes(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (philos[i].meal_mutex_init)
			pthread_mutex_destroy(&philos[i].meal_mutex);
		i++;
	}
}

static void	cleanup_all(t_app *app)
{
	int	count;
	int	i;

	count = app->config.philo_count;
	if (app->philos_ready && app->philos)
	{
		cleanup_philo_mutexes(app->philos, count);
		free(app->philos);
	}
	if (app->forks_ready && app->forks)
	{
		i = 0;
		while (i < count)
			pthread_mutex_destroy(&app->forks[i++].mtx);
		free(app->forks);
	}
	if (app->shared_ready)
	{
		pthread_mutex_destroy(&app->box.print_mutex);
		pthread_mutex_destroy(&app->box.state_mutex);
	}
}

static int	setup(int argc, char **argv, t_app *app)
{
	if (!parse_config(argc, argv, &app->config))
		return (put_err_msg(ERR_PARSE_MSG));
	if (!validate_config(&app->config))
		return (put_err_msg(ERR_VALID_MSG));
	if (!forks_init(&app->forks, app->config.philo_count))
		return (put_err_msg(ERR_FORKS_MSG));
	app->forks_ready = true;
	if (!shared_init(&app->box, &app->config))
		return (1);
	app->shared_ready = true;
	if (!philos_init(&app->philos, &app->box, app->forks))
		return (1);
	app->philos_ready = true;
	return (0);
}

static int	philosophers(int argc, char **argv)
{
	t_app	app;
	int		status;

	app.forks = NULL;
	app.philos = NULL;
	app.forks_ready = false;
	app.shared_ready = false;
	app.philos_ready = false;
	app.config.philo_count = 0;
	app.config.die_ms = 0;
	app.config.eat_ms = 0;
	app.config.sleep_ms = 0;
	app.config.must_eat = 0;
	status = setup(argc, argv, &app);
	if (status == 0 && !philos_start(app.philos, &app.box))
		status = 1;
	cleanup_all(&app);
	return (status);
}

int	main(int argc, char **argv)
{
	return (philosophers(argc, argv));
}
