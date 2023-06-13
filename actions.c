/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:02:07 by mlongo            #+#    #+#             */
/*   Updated: 2023/06/13 14:32:23 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	died(t_philo *philo)
{
	printf("%lu 1 is died\n", get_time());
}

void	eat(t_philo *philo)
{
	thinking();
	pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
	has_taken_a_fork(philo);
	thinking();
	if (philo->id == 0)
		pthread_mutex_lock(&philo->data->forks[philo->data->philo_num - 1]);
	else
		pthread_mutex_lock(&philo->data->forks[philo->id - 2]);
	philo->eat_cont++;
	philo->eating = 1;
	printf("%lu %d is eating\n", get_time(), philo->id);
	ft_usleep(philo->data->eat_time);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);

	printf("%lu 1 is eating\n", get_time());
}

void	has_taken_a_fork(t_philo *philo)
{
	printf("%lu %d has taken a fork\n", get_time(), philo->id);
}

void	sleep(t_philo *philo)
{
	printf("%lu 1 is sleeping\n", get_time());
}

void	thinking()
{
	printf("%lu 1 is thinking\n", get_time());
}
