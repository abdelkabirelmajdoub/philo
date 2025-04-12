/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:07:27 by ael-majd          #+#    #+#             */
/*   Updated: 2025/04/10 16:03:47 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *msg)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->print_metux);
	if (!philo->data->someone_die)
	{
		time = get_current_time() - philo->data->start_time;
		printf("%zu	%d %s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_metux);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->id % 2 == 0)
		usleep(500);
	if (philo->data->num_philos == 1)
		return (case_one(philo), NULL);
	while (!philo->data->someone_die)
	{
		eat_action(philo);
		if (philo->data->num_meals != -1 && 
			philo->meal == philo->data->num_meals)
			return (NULL);
		print_action(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep, philo);
		print_action(philo, "is thinking");
	}
	return (NULL);
}

void	*monitore(void *arg)
{
	t_data	*data;
	int		i;
	int		meals_done;

	data = (t_data *)arg;
	while (!data->someone_die)
	{
		i = 0;
		meals_done = 1;
		while (i < data->num_philos && !data->someone_die)
		{
			if (data->num_meals != -1 && data->philo[i].meal < data->num_meals)
				meals_done = 0;
			if (!data->philo[i].is_eating && get_current_time() - 
				data->philo[i].last_meal >= (size_t)data->time_to_die)
				return (death_action(data, &i), NULL);
			i++;
		}
		if (meals_done && data->num_meals != -1)
			break ;
		usleep(50);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	if (parsing(av, ac, &data))
		return (1);
	data.start_time = get_current_time();
	i = -1;
	while (++i < data.num_philos)
	{
		if (pthread_create(&data.philo[i].thread,
				NULL, &philo_routine, &data.philo[i]) != 0)
			return (1);
	}
	if (pthread_create(&data.death_lock, NULL, &monitore, &data) != 0)
		return (1);
	waitall_threads(&data);
	cleanup(&data);
}
