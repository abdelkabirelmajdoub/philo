/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:36:19 by ael-majd          #+#    #+#             */
/*   Updated: 2025/04/10 16:04:12 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(char **av, int ac, t_data *data)
{
	data->num_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->num_meals = -1;
	data->someone_die = 0;
	if (ac == 6)
		data->num_meals = ft_atoi(av[5]);
	if (data->num_philos > MAX_PHILOS)
		return (printf("Invalid number of Philosophers\n"), 1);
	if (data->num_philos <= 0 || data->time_to_die < 0)
		return (printf("Invalid number\n"), 1);
	if (data->time_to_sleep < 0 || data->time_to_eat < 0)
		return (printf("Invalid number\n"), 1);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	if (data->num_philos > MAX_PHILOS)
		return (1);
	i = -1;
	while (++i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philo[i].status_eat, NULL);
	}
	pthread_mutex_init(&data->print_metux, NULL);
	i = 0;
	while (i < data->num_philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		data->philo[i].data = data;
		data->philo[i].last_meal = get_current_time();
		i++;
	}
	return (0);
}

int	parsing(char **av, int ac, t_data *data)
{
	if (ac < 5 || ac > 6)
		return (printf("Wrong args count\n"), 1);
	if (check_input(av) < 0)
		return (1);
	if (init_data(av, ac, data))
		return (1);
	if (init_philos(data))
		return (1);
	return (0);
}

void	death_action(t_data *data, int *i)
{
	pthread_mutex_lock(&data->print_metux);
	data->someone_die = 1;
	printf("%zu	%d %s\n", get_current_time() - data->start_time, 
		data->philo[*i].id, "died");
	pthread_mutex_unlock(&data->print_metux);
}
