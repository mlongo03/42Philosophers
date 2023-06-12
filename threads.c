/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:28:12 by mlongo            #+#    #+#             */
/*   Updated: 2023/06/12 18:46:07 by mlongo           ###   ########.fr       */
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
