/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:43:28 by mlongo            #+#    #+#             */
/*   Updated: 2023/06/19 18:05:21 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	main2(int argc, t_data *data, pthread_t *monitor)
{
	int	i;

	i = 0;
	if (argc == 6)
	{
		if (pthread_create(monitor, NULL, &routinemonitor, data))
			return (1);
		pthread_detach(*monitor);
	}
	while (i < data->philo_num)
	{
		if (pthread_create(&data->tid[i], NULL,
				&routine_philo, &data->philos[i]))
			return (1);
		pthread_detach(data->tid[i]);
		ft_usleep(1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t	monitor;
	t_data		data;
	int			i;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		printf("Error\n");
		return (1);
	}
	if (init(&data, argv, argc))
		return (1);
	if (main2(argc, &data, &monitor))
		return (1);
	while (!data.dead && !data.finished)
		;
	ft_exit(&data);
	return (0);
}
