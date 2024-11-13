/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwozniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:55:12 by jwozniak          #+#    #+#             */
/*   Updated: 2024/08/10 16:55:14 by jwozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stddef.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_program	t_program;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					meals_eaten;
	long long			last_meal;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	t_program			*program;
}	t_philo;

typedef struct s_program
{
	int				*args;
	int				option_flag;
	int				end_flag;
	long long		start_time;
	pthread_mutex_t	end_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_program;

void		*philosopher_routine(void *arg);
void		*monitor_routine(void *arg);
long long	get_time_ms(void);
void		ft_usleep(long long ms);
void		print_state(t_philo *philo, const char *state);
void		think(t_philo *philo);
void		sleep_p(t_philo *philo);
void		take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		release_forks(t_philo *philo);
int			is_dead(t_philo *philo);
int			any_died(t_program *program);
int			all_philosophers_ate(t_program *program);
int			check_end_flag(t_program *program);
void		init_program(t_program *program, int argc, char **argv);
void		init_philos(t_program *program);
void		init_and_join_threads(t_program *program, pthread_t *threads);
void		cleanup(t_program *program);

#endif