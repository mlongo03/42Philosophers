/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:43:28 by mlongo            #+#    #+#             */
/*   Updated: 2023/06/14 15:02:22 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	init_philo(t_data *data)
{
	int i;

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
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->philo_num);
	data->tid = (pthread_t *)malloc(sizeof(pthread_mutex_t) * data->philo_num);
}

void	init(t_data *data, char **argv, int argc)
{
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

}

int	main(int argc, char **argv)
{
	pthread_t	monitor;
	t_data		data;
	int		i;

	i = 0;
	init(&data, argv, argc);
	// print_all_data(data);
	if (argc == 6)
	{
		if (pthread_create(&monitor, NULL, &routinemonitor, &data))
			return (1);
		pthread_detach(monitor);
	}
	while (i < data.philo_num)
	{
		if (pthread_create(&data.tid[i], NULL, &routinePhilo, &data.philos[i]))
			return (1);
		pthread_detach(data.tid[i]);
		ft_usleep(1);
		i++;
	}
	while (!data.dead && !data.finished)
		;
	// print_all_data(data);
	ft_exit(&data);
	return (0);
}
