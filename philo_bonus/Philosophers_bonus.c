/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:28:30 by mlongo            #+#    #+#             */
/*   Updated: 2023/06/19 17:40:48 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers_bonus.h"

void	init_philo(t_data *data)
{
	int		i;
	char	number[2];
	char	*itoa;

	i = 0;
	while (i < data->philo_num)
	{
		number[0] = '/';
		itoa = ft_itoa(i + 1);
		number[1] = itoa[0];
		sem_unlink(number);
		data->philos[i].sem_philo = sem_open(number, O_CREAT, 0644, 1);
		free(itoa);
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
	sem_unlink("/FORKS");
	sem_unlink("/WRITE");
	sem_unlink("/DATA");
	data->sem_forks = sem_open("/FORKS", O_CREAT, 0644, data->philo_num / 2);
	data->sem_write = sem_open("/WRITE", O_CREAT, 0644, 1);
	data->sem_data = sem_open("/DATA", O_CREAT, 0644, 1);
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
	data->pidmonitor = 0;
	init_sem(data);
	init_philo(data);
}

void	handle_meals(int exit_status, t_data *data)
{
	int	i;

	i = 0;
	if (WEXITSTATUS(exit_status) == 0 && data->meals_nb > 0)
	{
		while (i < data->philo_num && WEXITSTATUS(exit_status) == 0)
		{
			waitpid(data->pid[i], &exit_status, 0);
			i++;
		}
	}
	i = 0;
	while (i < data->philo_num)
		kill(data->pid[i++], SIGTERM);
}

int	main(int argc, char **argv)
{
	t_data		data;
	int			i;
	int			exit_status;

	if (argc != 5 && argc != 6)
	{
		printf("Error\n");
		return (0);
	}
	exit_status = 0;
	init(&data, argv, argc);
	data.pid = (int *)malloc(sizeof(int) * data.philo_num);
	i = 0;
	while (i < data.philo_num)
	{
		data.pid[i] = fork();
		if (data.pid[i] == 0)
			routine_philo(&data.philos[i]);
		i++;
	}
	waitpid(-1, &exit_status, 0);
	handle_meals(exit_status, &data);
	ft_exit(&data);
	return (0);
}
