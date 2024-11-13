/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwozniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:02:26 by jwozniak          #+#    #+#             */
/*   Updated: 2024/08/10 17:02:32 by jwozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	if (check_end_flag(philo->program))
		return ;
	print_state(philo, "is thinking");
}

void	eat(t_philo *philo)
{
	if (check_end_flag(philo->program))
		return ;
	print_state(philo, "is eating");
	pthread_mutex_lock(&philo->program->dead_lock);
	pthread_mutex_lock(&philo->program->meal_lock);
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->program->dead_lock);
	pthread_mutex_unlock(&philo->program->meal_lock);
	ft_usleep(philo->program->args[2]);
	release_forks(philo);
}

void	sleep_p(t_philo *philo)
{
	if (check_end_flag(philo->program))
		return ;
	print_state(philo, "is sleeping");
	ft_usleep(philo->program->args[3]);
}

int	is_dead(t_philo *philo)
{
	long long	current_time;
	long long	death_time;

	current_time = get_time_ms();
	death_time = philo->last_meal + philo->program->args[1];
	return (current_time > death_time);
}
