/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:37:46 by ael-majd          #+#    #+#             */
/*   Updated: 2025/04/10 16:04:03 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		if (philo->data->someone_die)
			break ;
		usleep(500);
	}
	return (0);
}

void	waitall_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return ;
	}
	if (pthread_join(data->death_lock, NULL) != 0)
		return ;
}

void	cleanup(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].status_eat);
	}
	pthread_mutex_destroy(&data->print_metux);
}
