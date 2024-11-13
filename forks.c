/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwozniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:22:42 by jwozniak          #+#    #+#             */
/*   Updated: 2024/11/13 15:22:44 by jwozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

static int	lock_fork(pthread_mutex_t *fork, t_philo *philo)
{
	pthread_mutex_lock(fork);
	if (check_end_flag(philo->program))
	{
		pthread_mutex_unlock(fork);
		return (1);
	}
	return (0);
}

static int	lock_and_print(pthread_mutex_t *fork,
	t_philo *philo, const char *action)
{
	if (lock_fork(fork, philo))
		return (1);
	print_state(philo, action);
	return (0);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (check_end_flag(philo->program))
		return ;
	if (philo->id % 2 == 0)
	{
		first_fork = philo->r_fork;
		second_fork = philo->l_fork;
	}
	else
	{
		first_fork = philo->l_fork;
		second_fork = philo->r_fork;
	}
	if (lock_and_print(first_fork, philo, "has taken a fork"))
		return ;
	if (lock_and_print(second_fork, philo, "has taken a fork"))
	{
		release_forks(philo);
		return ;
	}
}
