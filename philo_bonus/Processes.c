/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:34:36 by mlongo            #+#    #+#             */
/*   Updated: 2023/06/16 17:17:44 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers_bonus.h"

void	*routinemonitor(void *data2)
{
	int		i;
	t_data	*data;

	i = 0;
	data = (t_data *)data2;
	while (i < data->philo_num - 1)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	ft_exit(data);
	exit (1);
}

void	*routine_supervisor(void *philo2)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)philo2;
	while (!philo->data->dead && !philo->data->finished)
	{
		sem_wait(philo->sem_philo);
		sem_wait(philo->data->sem_data);
		if (philo->data->meals_nb != -1)
			if (philo->eat_cont == philo->data->meals_nb)
				kill(philo->data->pidmonitor, SIGUSR1);
		sem_post(philo->sem_philo);
		sem_post(philo->data->sem_data);
		sem_wait(philo->sem_philo);
		if ((get_time() >= philo->time_to_die) && !philo->eating)
		{
			sem_post(philo->sem_philo);
			sem_wait(philo->data->sem_data);
			died(philo);
			philo->data->dead = 1;
			ft_usleep(10000);
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
	printf("OK\n");
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
	ft_exit(philo->data);
	exit (1);
}
