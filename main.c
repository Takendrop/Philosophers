/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwozniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:55:03 by jwozniak          #+#    #+#             */
/*   Updated: 2024/08/10 16:55:05 by jwozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->program->end_lock);
		if (philo->program->end_flag)
		{
			pthread_mutex_unlock(&philo->program->end_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->program->end_lock);
		think(philo);
		take_forks(philo);
		eat(philo);
		sleep_p(philo);
	}
	return (NULL);
}

int	any_died(t_program *program)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&program->dead_lock);
	while (i < program->args[0])
	{
		if (is_dead(&program->philos[i]))
		{
			print_state(&program->philos[i], "died");
			pthread_mutex_unlock(&program->dead_lock);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&program->dead_lock);
	return (0);
}

int	all_philosophers_ate(t_program *program)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&program->meal_lock);
	while (i < program->args[0])
	{
		if (program->philos[i].meals_eaten < program->args[4])
		{
			pthread_mutex_unlock(&program->meal_lock);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&program->meal_lock);
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_program	*program;

	program = (t_program *)arg;
	while (1)
	{
		if (any_died(program))
		{
			pthread_mutex_lock(&program->end_lock);
			program->end_flag = 1;
			pthread_mutex_unlock(&program->end_lock);
			break ;
		}
		if (program->option_flag)
		{
			if (all_philosophers_ate(program))
			{
				pthread_mutex_lock(&program->end_lock);
				program->end_flag = 1;
				pthread_mutex_unlock(&program->end_lock);
				break ;
			}
		}
		usleep(300);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_program	program;
	pthread_t	*threads;

	if (argc < 5 || argc > 6)
	{
		printf("Run with minimum of 4 arguments!");
		return (1);
	}
	init_program(&program, argc, argv);
	init_philos(&program);
	threads = (pthread_t *)malloc(program.args[0] * sizeof(pthread_t));
	if (!threads)
	{
		perror("malloc");
		return (1);
	}
	init_and_join_threads(&program, threads);
	cleanup(&program);
	free(threads);
	return (0);
}
