/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 00:53:36 by kyanagis          #+#    #+#             */
/*   Updated: 2025/10/29 14:12:17 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_config
{
	int				philo_count;
	int				die_ms;
	int				eat_ms;
	int				sleep_ms;
	int				must_eat;
}					t_config;

typedef struct s_fork
{
	int				id;
	bool			taken;
	pthread_mutex_t	mtx;
}					t_fork;

typedef struct s_shared
{
	t_config		cfg;
	long long		start_us;
	int				started;
	int				stop;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	print_mutex;
}					t_shared;

typedef struct s_philo
{
	int				id;
	t_shared		*box;
	t_fork			*left;
	t_fork			*right;

	t_fork			*first;
	t_fork			*second;

	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	bool			meal_mutex_init;
	long long		last_meal_us;
	int				meals_done;
}					t_philo;

typedef struct s_app
{
	t_config	config;
	t_fork		*forks;
	t_shared	box;
	t_philo		*philos;
	bool		forks_ready;
	bool		shared_ready;
	bool		philos_ready;
}					t_app;

void				print_state(t_shared *box, int id, const char *msg);
void				print_state_at(t_shared *box, long long timestamp_us,
						int id, const char *msg);
void				print_death(t_shared *box, long long timestamp_us,
						int id);
bool				is_tight_even_cycle(const t_config *cfg);
void				stagger_start(t_philo *ph);
void				think(t_philo *ph, long long think_start_us);
long long			calc_sleep_end_us(t_philo *ph, long long end_eat_us);
void				handle_single_philo(t_philo *ph);
bool				take_two_forks(t_philo *ph, long long *out_start_us);
void				release_two_forks(t_philo *ph);
bool				do_eat(t_philo *ph, long long *out_end_us);
bool				wait_for_start(t_shared *box);
bool				should_stop(t_shared *box);
bool				set_stop(t_shared *box);
void				*philo_routine(void *arg);
void				*monitor(void *arg);
bool				philos_start(t_philo *philos, t_shared *box);
void				sleep_until(t_shared *box, long long target_us);
int					put_err_msg(const char *msg);
size_t				ft_strlen(const char *msg);
long long			now_ms(void);
long long			now_us(void);
bool				shared_init(t_shared *box, t_config *config);
bool				philos_init(t_philo **out_philo, t_shared *box,
						t_fork *forks);
bool				forks_init(t_fork **out_forks, int count);
bool				parse_config(int argc, char **argv, t_config *config);
bool				validate_config(const t_config *config);
#endif
