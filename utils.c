/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwozniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:55:18 by jwozniak          #+#    #+#             */
/*   Updated: 2024/08/10 16:55:19 by jwozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_ms(void)
{
	struct timeval	tv;
	long long		time_ms;

	gettimeofday(&tv, NULL);
	time_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_ms);
}

void	ft_usleep(long long ms)
{
	usleep(ms * 1000);
}

int	check_end_flag(t_program *program)
{
	int	end_flag;

	pthread_mutex_lock(&program->end_lock);
	end_flag = program->end_flag;
	pthread_mutex_unlock(&program->end_lock);
	return (end_flag);
}

void	print_state(t_philo *philo, const char *state)
{
	long long		timestamp;

	if (check_end_flag(philo->program))
		return ;
	pthread_mutex_lock(&philo->program->write_lock);
	timestamp = get_time_ms() - philo->program->start_time;
	printf("%lld %d %s\n", timestamp, philo->id, state);
	pthread_mutex_unlock(&philo->program->write_lock);
}

void	cleanup(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->args[0])
	{
		pthread_mutex_destroy(&program->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&program->end_lock);
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->write_lock);
	free(program->philos);
	free(program->forks);
	free(program->args);
}
