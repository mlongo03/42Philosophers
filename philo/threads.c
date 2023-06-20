/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:28:12 by mlongo            #+#    #+#             */
/*   Updated: 2023/06/20 17:06:04 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*routinemonitor(void *data2)
{
	int		i;
	t_data	*data;

	i = 0;
	data = (t_data *)data2;
	while (!data->finished && !data->dead)
	{
		i = 0;
		while (i < data->philo_num)
		{
			if (data->philos[i].eat_cont < data->meals_nb)
				break ;
			i++;
		}
		if (i == data->philo_num)
		{
			pthread_mutex_lock(&data->lock);
			data->finished = 1;
			ft_usleep(100);
			pthread_mutex_unlock(&data->lock);
		}
	}
	return (NULL);
}

void	*routine_supervisor(void *philo2)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)philo2;
	while (!philo->data->dead && !philo->data->finished)
	{
		pthread_mutex_lock(&philo->lock);
		if ((get_time() >= philo->time_to_die) && !philo->eating)
		{
			pthread_mutex_unlock(&philo->lock);
			pthread_mutex_lock(&philo->data->lock);
			died(philo);
			philo->data->dead = 1;
			ft_usleep(10000);
			pthread_mutex_unlock(&philo->data->write);
			pthread_mutex_unlock(&philo->data->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->lock);
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
	return (NULL);
}
