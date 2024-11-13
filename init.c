/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwozniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:16:57 by jwozniak          #+#    #+#             */
/*   Updated: 2024/08/10 17:16:58 by jwozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_program(t_program *program, int argc, char **argv)
{
	int				i;

	program->args = (int *)malloc((argc - 1) * sizeof(int));
	if (!program->args)
	{
		perror("malloc");
		exit(1);
	}
	i = 1;
	while (i < argc)
	{
		program->args[i - 1] = atoi(argv[i]);
		i++;
	}
	if (argc == 5)
		program->option_flag = 0;
	else if (argc == 6)
		program->option_flag = 1;
	program->end_flag = 0;
	program->start_time = get_time_ms();
	pthread_mutex_init(&program->end_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
}

pthread_mutex_t	*init_forks(int num_forks)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *)malloc(num_forks * sizeof(pthread_mutex_t));
	if (!forks)
	{
		perror("malloc");
		exit(1);
	}
	i = 0;
	while (i < num_forks)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

void	init_philosophers(t_program *program, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < program->args[0])
	{
		program->philos[i].id = i + 1;
		program->philos[i].meals_eaten = 0;
		program->philos[i].last_meal = get_time_ms();
		program->philos[i].r_fork = &forks[i];
		program->philos[i].l_fork = &forks[(i + 1) % program->args[0]];
		program->philos[i].program = program;
		i++;
	}
}

void	init_philos(t_program *program)
{
	pthread_mutex_t	*forks;

	forks = init_forks(program->args[0]);
	program->forks = forks;
	program->philos = (t_philo *)malloc(program->args[0] * sizeof(t_philo));
	if (!program->philos)
	{
		perror("malloc");
		exit(1);
	}
	init_philosophers(program, forks);
}

void	init_and_join_threads(t_program *program, pthread_t *threads)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < program->args[0])
	{
		pthread_create(&threads[i], NULL, philosopher_routine,
			&program->philos[i]);
		usleep(100);
		i++;
	}
	pthread_create(&monitor_thread, NULL, monitor_routine, program);
	i = 0;
	while (i < program->args[0])
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}
