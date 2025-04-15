/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:18:17 by ael-majd          #+#    #+#             */
/*   Updated: 2025/04/15 13:45:23 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_data *data)
{
	int i;

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

int main(int ac, char **av)
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
	return  (0);
}
