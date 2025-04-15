/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:30:31 by ael-majd          #+#    #+#             */
/*   Updated: 2025/04/15 14:47:38 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *msg)
{
	size_t	time;

	if (is_death(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->print);
	if (!is_death(philo->data))
	{
		time = get_time() - philo->data->start_time;
		printf("%zu %d %s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print);
}

void eating(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_action(philo, "has taking a fork");
	pthread_mutex_lock(philo->r_fork);
	print_action(philo, "has taking a fork");
	print_action(philo, "is eating");

	pthread_mutex_lock(&philo->data->meal_check);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_check);
	
	ft_usleep(philo->data->t_eat);

	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void dreaming(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->data->t_sleep);
}

int	end_simulation(t_data *data, int *i)
{
	pthread_mutex_lock(&data->meal_check);
	if (get_time() - data->philo[*i].last_meal >= (size_t)data->t_die)
	{
		pthread_mutex_lock(&data->death_check);
		data->died_flag = 1;
		printf("%zu %d died\n", get_time() - data->start_time,
			data->philo[*i].id);
		pthread_mutex_unlock(&data->death_check);
		pthread_mutex_unlock(&data->meal_check);
		return (1);
	}
	pthread_mutex_unlock(&data->meal_check);
	return (0);
}