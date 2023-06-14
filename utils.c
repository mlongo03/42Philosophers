/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:03:39 by mlongo            #+#    #+#             */
/*   Updated: 2023/06/14 16:44:37 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	error(char *str, t_data *data)
{
	printf("%s\n", str);
	if (data)
		ft_exit(data);
	return (1);
}

void	clear_data(t_data	*data)
{
	if (data->tid)
		free(data->tid);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	clear_data(data);
}

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error("gettimeofday() FAILURE\n", NULL));
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(u_int64_t time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

/*void	print_all_data (t_data data)
{
	int	i;

	i = 0;
	printf("DATA:");
	printf("dead : %d\ndeath_time : %llu\neat_time : %llu\nfinished : %d\nmeals_nb : %d\nphilo_num : %d\nsleep time : %llu\nstart_time : %llu\n", data.dead, data.death_time, data.eat_time, data.finished, data.meals_nb, data.philo_num, data.sleep_time, data.start_time);
	while (i < data.philo_num)
	{
		printf("PHILO N %d\n", data.philos[i].id);
		printf("eat_cont : %d\neating : %d\nstatus : %d\ntime_to_die : %llu\n", data.philos[i].eat_cont, data.philos[i].eating, data.philos[i].status, data.philos[i].time_to_die);
		i++;
	}
}*/
