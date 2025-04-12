/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:04:35 by ael-majd          #+#    #+#             */
/*   Updated: 2025/04/10 16:03:42 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# define MAX_PHILOS 200

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meal;
	int				is_eating;
	size_t			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	status_eat;
	t_data			*data;
}					t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				someone_die;
	int				num_meals;
	size_t			start_time;
	pthread_mutex_t	forks[MAX_PHILOS];
	pthread_mutex_t	print_metux;
	pthread_t		death_lock;
	t_philo			philo[MAX_PHILOS];
}					t_data;

size_t	get_current_time(void);
int		parsing(char **av, int ac, t_data *data);
int		ft_usleep(size_t milliseconds, t_philo *philo);
int		ft_atoi(char *s);
int		check_input(char **av);
void	cleanup(t_data *data);
void	waitall_threads(t_data *data);
void	case_one(t_philo *philo);
void	print_action(t_philo *philo, char *msg);
void	eat_action(t_philo *philo);
void	death_action(t_data *data, int *i);
#endif
