/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:34:36 by mlongo            #+#    #+#             */
/*   Updated: 2023/06/19 17:43:48 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers_bonus.h"

void	check_meals(t_philo *philo)
{
	sem_wait(philo->sem_philo);
	sem_wait(philo->data->sem_data);
	if (philo->data->meals_nb != -1)
		if (philo->eat_cont == philo->data->meals_nb)
			philo->data->finished = 1;
	sem_post(philo->sem_philo);
	sem_post(philo->data->sem_data);
}

void	*routine_supervisor(void *philo2)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)philo2;
	while (!philo->data->dead && !philo->data->finished)
	{
		check_meals(philo);
		sem_wait(philo->sem_philo);
		if ((get_time() >= philo->time_to_die) && !philo->eating)
		{
			sem_post(philo->sem_philo);
			sem_wait(philo->data->sem_data);
			died(philo);
			philo->data->dead = 1;
			exit (1);
			sem_post(philo->data->sem_write);
			sem_post(philo->data->sem_data);
			break ;
		}
		sem_post(philo->sem_philo);
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
		if (philo->data->finished)
			break ;
		mine_sleep(philo);
		if (philo->data->finished)
			break ;
		thinking(philo);
	}
	ft_exit(philo->data);
	exit (0);
}
