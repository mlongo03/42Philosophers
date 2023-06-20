/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:46:39 by mlongo            #+#    #+#             */
/*   Updated: 2023/06/19 18:04:52 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].data = data;
		data->philos[i].eat_cont = 0;
		data->philos[i].eating = 0;
		data->philos[i].id = i + 1;
		data->philos[i].time_to_die = get_time() + data->death_time;
		data->philos[i].r_fork = &data->forks[i];
		if (i == 0)
			data->philos[i].l_fork = &data->forks[data->philo_num - 1];
		else
			data->philos[i].l_fork = &data->forks[i - 1];
		pthread_mutex_init(&data->philos[i].lock, NULL);
		data->philos[i].status = 0;
		i++;
	}
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->write, NULL);
}

void	storage(t_data *data)
{
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_num);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->philo_num);
	data->tid = (pthread_t *)malloc(sizeof(pthread_mutex_t) * data->philo_num);
}

int	init(t_data *data, char **argv, int argc)
{
	if (ft_atoi(argv[1]) == -2 || ft_atoi(argv[2]) == -2
		|| ft_atoi(argv[3]) == -2 || ft_atoi(argv[4]) == -2)
		return (1);
	if (argc == 6)
		if (ft_atoi(argv[5]) == -2)
			return (1);
	data->philo_num = ft_atoi(argv[1]);
	data->finished = 0;
	data->dead = 0;
	if (argc == 6)
		data->meals_nb = ft_atoi(argv[5]);
	else
		data->meals_nb = -1;
	data->sleep_time = (u_int64_t)ft_atoi(argv[4]);
	data->death_time = (u_int64_t)ft_atoi(argv[2]);
	data->eat_time = (u_int64_t)ft_atoi(argv[3]);
	data->start_time = get_time();
	storage(data);
	init_mutex(data);
	init_philo(data);
	return (0);
}
