/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:34:36 by mlongo            #+#    #+#             */
/*   Updated: 2023/06/16 12:50:45 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers_bonus.h"

void	*routine_supervisor(void *philo2)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)philo2;
	while (!philo->data->dead && !philo->data->finished)
	{
		sem_wait(&philo->sem_philo);
		if ((get_time() >= philo->time_to_die) && !philo->eating)
		{
			sem_post(&philo->sem_philo);
			sem_wait(&philo->data->sem_data);
			died(philo);
			philo->data->dead = 1;
			ft_usleep(10000);
			sem_post(&philo->data->sem_write);
			sem_post(&philo->data->sem_data);
			break ;
		}
		sem_post(&philo->sem_philo);
	}
	return (NULL);
}

void	*routine_philo(void	*philo2)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)philo2;
	if (pthread_create(&philo->t1, NULL, &routine_supervisor, (void *)philo))
		return (NULL);
	pthread_detach(philo->t1);
	while (!philo->data->dead && !philo->data->finished)
	{
		eat(philo);
		mine_sleep(philo);
		thinking(philo);
	}
	exit (1);
}
