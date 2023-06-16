/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:28:30 by mlongo            #+#    #+#             */
/*   Updated: 2023/06/16 12:33:47 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers_bonus.h"

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		sem_unlink(ft_itoa(i + 1));
		data->philos[i].sem_philo = sem_open(ft_itoa(i + 1), O_CREATE, 1);
		data->philos[i].data = data;
		data->philos[i].eat_cont = 0;
		data->philos[i].eating = 0;
		data->philos[i].id = i + 1;
		data->philos[i].time_to_die = get_time() + data->death_time;
		data->philos[i].status = 0;
		i++;
	}
}

void	init_sem(t_data *data)
{
	int	i;

	i = 0;
	i = 0;
	sem_unlink("FORKS");
	sem_unlink("WRITE");
	sem_unlink("DATA");
	data->sem_forks = sem_open("FORKS", O_CREATE, ft_atoi(argv[1]));
	data->sem_write = sem_open("WRITE", O_CREATE, 1);
	data->sem_write = sem_open("DATA", O_CREATE, 1);
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
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_num);
	init_sem(data);
	init_philo(data);
}

int	main(int argc, char **argv)
{
	pthread_t	monitor;
	t_data		data;
	int			i;
	int			*pid;

// INIZIALIZATION OF EVERY STRUCT

	init(&data, argv, argc);

// CREATION OF PROCESSES OF EVERY PHILO

	pid = (int *)malloc(sizeof(int) * data.philo_num);
	i = 0;
	while (i < data.philo_num)
	{
		pid[i] = fork();
		if (pid == 0)
			routine_philo(&data.philos[i]);
		i++;
	}

// WAIT UNTIL EVERY PROCESS IS FINISHED, THEN FREE AND EXIT

	waitpid(-1, NULL, 0);
	ft_exit(&data);
	return (0);
}
