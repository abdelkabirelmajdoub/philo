/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:18:40 by ael-majd          #+#    #+#             */
/*   Updated: 2025/04/10 15:19:01 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (printf("Bad args: Invalid input\n"), -1);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_atoi(char *s)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while (s[i] && s[i] == ' ')
		i++;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - '0');
		if (res > 2147483647)
			return (-1);
		i++;
	}
	return (res);
}

void	case_one(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die, philo);
	pthread_mutex_unlock(philo->left_fork);
}

void	eat_action(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->status_eat);
	print_action(philo, "is eating");
	ft_usleep(philo->data->time_to_eat, philo);
	philo->is_eating = 1;
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->status_eat);
	pthread_mutex_lock(&philo->status_eat);
	philo->is_eating = 0;
	philo->meal++;
	pthread_mutex_unlock(&philo->status_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
