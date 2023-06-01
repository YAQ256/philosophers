/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:55:28 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/06/01 13:22:43 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	struct timeval		tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		printf("Error : gettime failed\n");
		return (-1);
	}
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->reaper);
	if (philo->data->dead >= 0 || philo->data->dead == -philo->id)
		printf("%ld %d %s\n", get_time() - philo->data->t_t_start, \
			philo->id, str);
	pthread_mutex_unlock(&philo->data->reaper);
}

int	ft_died(t_philo *philo)
{
	if (get_time() - philo->time_last_meal >= philo->data->t_t_d)
	{
		pthread_mutex_lock(&philo->data->reaper);
		if (philo->data->dead < 0)
		{
			pthread_mutex_unlock(&philo->data->reaper);
			return (1);
		}
		philo->data->dead = -philo->id;
		pthread_mutex_unlock(&philo->data->reaper);
		ft_print(philo, "died");
		return (2);
	}
	return (0);
}

int	is_end(t_data *data)
{
	pthread_mutex_lock(&data->reaper);
	if (data->dead < 0 || data->dead == data->n_philo)
	{
		pthread_mutex_unlock(&data->reaper);
		return (1);
	}
	pthread_mutex_unlock(&data->reaper);
	return (0);
}
