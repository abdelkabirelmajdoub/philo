/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:18:17 by ael-majd          #+#    #+#             */
/*   Updated: 2025/05/01 13:12:50 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	creat_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		if (pthread_create(&data->philo[i].thread, NULL, 
				&routine, &data->philo[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&data->observer, NULL, &monitore, data) != 0)
		return (1); 
	return (0);
}

int	wait_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_join(data->observer, NULL) != 0)
		return (1);
	return (0);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->meal_check);
	pthread_mutex_destroy(&data->death_check);
	pthread_mutex_destroy(&data->print);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (check_input(ac, av))
		return (1);
	if (init(&data, av))
		return (1);
	if (creat_join(&data))
		return (1);
	if (wait_threads(&data))
		return (1);
	cleanup(&data);
	return (0);
}
