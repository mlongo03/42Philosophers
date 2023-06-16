/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:02:07 by mlongo            #+#    #+#             */
/*   Updated: 2023/06/16 12:41:57 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write);
	printf("%llu %d is died\n", get_time() - philo->data->start_time, philo->id);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	has_taken_a_fork(philo);
	pthread_mutex_lock(philo->r_fork);
	has_taken_a_fork(philo);
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_lock(&philo->data->lock);
	philo->eat_cont++;
	philo->eating = 1;
	philo->time_to_die = get_time() + philo->data->death_time;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_lock(&philo->data->write);
	printf("%llu %d is eating\n", get_time()
		- philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->write);
	ft_usleep(philo->data->eat_time);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	has_taken_a_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write);
	printf("%llu %d has taken a fork\n", get_time()
		- philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->write);
}

void	mine_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write);
	printf("%llu %d is sleeping\n", get_time()
		- philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->write);
	ft_usleep(philo->data->sleep_time);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write);
	printf("%llu %d is thinking\n", get_time()
		- philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->write);
}
