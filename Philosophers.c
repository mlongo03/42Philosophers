/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:43:28 by mlongo            #+#    #+#             */
/*   Updated: 2023/06/12 18:27:40 by mlongo           ###   ########.fr       */
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
		data->philos[i].time_to_die = 0;
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
	data->death_time = (u_int64_t)ft_atoi(argv[3]);
	data->eat_time = (u_int64_t)ft_atoi(argv[2]);
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
	// printf("DATA:");
	// printf("dead : %d\ndeath_time : %lu\neat_time : %lu\nfinished : %d\nmeals_nb : %d\nphilo_num : %d\nsleep time : %lu\nstart_time : %lu\n", data.dead, data.death_time, data.eat_time, data.finished, data.meals_nb, data.philo_num, data.sleep_time, data.start_time);
	// while (i < data.philo_num)
	// {
	// 	printf("PHLO N %d\n", data.philos[i++].id);
	// 	printf("eat_cont : %d\neating : %d\nstatus : %d\ntime_to_die : %lu\n", data.philos[i].eat_cont, data.philos[i].eating, data.philos[i].status, data.philos[i].time_to_die);
	// }
	if (argc == 6)
		pthread_create(&monitor, NULL, &routinemonitor, &data);
	return (0);
}
