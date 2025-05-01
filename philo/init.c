/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:18:50 by ael-majd          #+#    #+#             */
/*   Updated: 2025/05/01 13:10:55 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_data_arg(t_data *data)
{
	if (data->nbr_philos <= 0 || data->t_die <= 0 || data->t_eat <= 0)
		return (1);
	if (data->t_sleep <= 0)
		return (1);
	if (data->nbr_philos >= 200)
		return (1);
	if (data->meals_req != -1 && data->meals_req < 1)
		return (1);
	return (0);
}

int	data_init(char **av, t_data *data)
{
	int	i;

	data->nbr_philos = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (av[5])
		data->meals_req = ft_atoi(av[5]);
	else
		data->meals_req = -1;
	if (check_data_arg(data))
		return (write(2, "incorrect number\n", 17), 1);
	pthread_mutex_init(&data->death_check, NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->meal_check, NULL);
	data->start_time = get_time();
	i = 0;
	while (i < data->nbr_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	philo_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meals_eaten = 0;
		data->philo[i].last_meal = data->start_time;
		data->philo[i].data = data;
		data->philo[i].l_fork = &data->forks[i];
		data->philo[i].r_fork = &data->forks[(i + 1) % data->nbr_philos];
	}
	return (0);
}

int	init(t_data *data, char **av)
{
	if (data_init(av, data))
		return (1);
	if (philo_init(data))
		return (1);
	return (0);
}
