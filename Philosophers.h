/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:16:49 by mlongo            #+#    #+#             */
/*   Updated: 2023/06/14 16:36:57 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <stdbool.h>
# include <stdint.h>

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t1;
	int				id;
	int				eat_cont;
	int				status;
	int				eating;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_data
{
	pthread_t		*tid;
	int				philo_num;
	int				meals_nb;
	int				dead;
	int				finished;
	t_philo			*philos;
	u_int64_t		death_time;
	u_int64_t		eat_time;
	u_int64_t		sleep_time;
	u_int64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_data;

int			error(char *str, t_data *data);
u_int64_t	get_time(void);
int			ft_atoi(const char *nptr);
void		init_philo(t_data *data);
void		ft_exit(t_data *data);
void		clear_data(t_data	*data);
void		*routinemonitor(void *data2);
int			ft_usleep(u_int64_t time);
void		print_all_data(t_data data);
void		*routine_philo(void	*philo2);
void		*routine_supervisor(void *philo2);
void		died(t_philo *philo);
void		eat(t_philo *philo);
void		has_taken_a_fork(t_philo *philo);
void		mine_sleep(t_philo *philo);
void		thinking(t_philo *philo);

#endif
