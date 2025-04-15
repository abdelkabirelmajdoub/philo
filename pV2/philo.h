/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:04:27 by ael-majd          #+#    #+#             */
/*   Updated: 2025/04/15 14:47:34 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#define MAX_PHILOS 200

typedef struct s_data t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	size_t			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_data			*data;
}					t_philo;

typedef struct s_data
{
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				died_flag;
	int				meals_req;
	int				nbr_philos;
	size_t			start_time;
	pthread_mutex_t	forks[MAX_PHILOS];
	pthread_mutex_t	print;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	death_check;
	pthread_t		observer;
	t_philo			philo[MAX_PHILOS];
}					t_data;

int		ft_atoi(char *s);
int		check_input(int ac, char **av);
size_t	get_time(void);
int		ft_usleep(size_t milliseconds);
int		init(t_data *data, char **av);
int		creat_join(t_data *data);
int		wait_threads(t_data *data);
void	*routine(void *arg);
int		is_death(t_data *data);
void	print_action(t_philo *philo, char *msg);
void	eating(t_philo *philo);
void	dreaming(t_philo *philo);
int		end_simulation(t_data *data, int *i);

#endif