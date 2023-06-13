/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:28:12 by mlongo            #+#    #+#             */
/*   Updated: 2023/06/13 12:52:31 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*routinemonitor(void *data2)
{
	int		i;
	t_data	*data;

	i = 0;
	data = (t_data *)data2;
	while (1)
	{
		i = 0;
		while (i < data->philo_num)
		{
			if (data->philos[i].eat_cont >= data->meals_nb)
				break ;
			i++;
		}
		if (i == data->philo_num - 1)
			break ;
	}
	data->finished = 1;
}

void	*routineSupervisor(void *philo2)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)philo2;
	while (!philo->data->dead)
	{
		ft_usleep(1);
		philo->time_to_die++;
		if (philo->time_to_die == philo->data->dead && !philo->eating)
			dead();
		if (philo->eating)
			philo->time_to_die = 0;
	}
}

void	*routinePhilo(void	*philo2)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)philo2;
	if (pthread_create(&philo->t1, NULL, &routineSupervisor, (void *)philo))
		return (1);
	while (!philo->data->dead)
	{
		eat();
		sleep();
	}
}
