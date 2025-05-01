/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:49:11 by ael-majd          #+#    #+#             */
/*   Updated: 2025/04/20 14:54:46 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_death(t_data *data)
{
	int	resulte;

	pthread_mutex_lock(&data->death_check);
	resulte = data->died_flag;
	pthread_mutex_unlock(&data->death_check);
	return (resulte);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nbr_philos == 1)
	{
		print_action(philo, "has taking a fork");
		ft_usleep(philo->data->t_die, philo->data);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(2000);
	while (!is_death(philo->data))
	{
		eating(philo);
		dreaming(philo);
		print_action(philo, "is thinking");
	}
	return (NULL);
}

int	check_all_ate(t_data *data)
{
	int	i;
	int	all_ate;

	i = 0;
	all_ate = 1;
	while (i < data->nbr_philos)
	{
		pthread_mutex_lock(&data->meal_check);
		if (data->philo[i].meals_eaten < data->meals_req
			|| data->meals_req == -1)
			all_ate = 0;
		pthread_mutex_unlock(&data->meal_check);
		i++;
	}
	return (all_ate);
}

void	*monitore(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!is_death(data))
	{
		i = 0;
		while (i < data->nbr_philos)
		{
			if (end_simulation(data, &i))
				return (NULL);
			i++;
		}
		if (check_all_ate(data))
		{
			pthread_mutex_lock(&data->death_check);
			data->died_flag = 1;
			pthread_mutex_unlock(&data->death_check);
			break ;
		}
	}
	return (NULL);
}
