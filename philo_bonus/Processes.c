/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:34:36 by mlongo            #+#    #+#             */
/*   Updated: 2023/06/15 17:35:10 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers_bonus.h"

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
