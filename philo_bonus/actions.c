/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:38:20 by mlongo            #+#    #+#             */
/*   Updated: 2023/06/16 17:04:53 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers_bonus.h"

void	died(t_philo *philo)
{
	sem_wait(philo->data->sem_write);
	printf("%llu %d is died\n", get_time() - philo->data->start_time, philo->id);
	//ricordati di aggiungere il sem_post nel supervisor
}

void	eat(t_philo *philo)
{
	sem_wait(philo->data->sem_forks);
	has_taken_a_fork(philo);
	has_taken_a_fork(philo);
	sem_wait(philo->sem_philo);
	sem_wait(philo->data->sem_data);
	philo->eat_cont++;
	philo->eating = 1;
	philo->time_to_die = get_time() + philo->data->death_time;
	sem_post(philo->sem_philo);
	sem_post(philo->data->sem_data);
	sem_wait(philo->data->sem_write);
	printf("%llu %d is eating\n", get_time()
		- philo->data->start_time, philo->id);
	sem_post(philo->data->sem_write);
	ft_usleep(philo->data->eat_time);
	sem_wait(philo->sem_philo);
	philo->eating = 0;
	sem_post(philo->sem_philo);
	sem_post(philo->data->sem_forks);
}

void	has_taken_a_fork(t_philo *philo)
{
	sem_wait(philo->data->sem_write);
	printf("%llu %d has taken a fork\n", get_time()
		- philo->data->start_time, philo->id);
	sem_post(philo->data->sem_write);
}

void	mine_sleep(t_philo *philo)
{
	sem_wait(philo->data->sem_write);
	printf("%llu %d is sleeping\n", get_time()
		- philo->data->start_time, philo->id);
	sem_post(philo->data->sem_write);
	ft_usleep(philo->data->sleep_time);
}

void	thinking(t_philo *philo)
{
	sem_wait(philo->data->sem_write);
	printf("%llu %d is thinking\n", get_time()
		- philo->data->start_time, philo->id);
	sem_post(philo->data->sem_write);
}
