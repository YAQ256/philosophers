/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:51:05 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/06/01 14:56:43 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_init(t_data *data)
{
	int	i;

	data->philo = malloc(data->n_philo * sizeof(t_philo));
	if (!data->philo)
		return (printf("Error : malloc failed\n"));
	i = 0;
	while (i < data->n_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].id_thread = 0;
		data->philo[i].time_last_meal = 0;
		data->philo[i].n_meal = 0;
		if (pthread_mutex_init(&data->philo[i].m_fork_left, NULL))
			return (free(data->philo), 1);
		data->philo[i].fork_left = 0;
		data->philo[i].m_fork_right = \
			&data->philo[(i + 1) % data->n_philo].m_fork_left;
		data->philo[i].fork_right = \
			&data->philo[(i + 1) % data->n_philo].fork_left;
		if (data->n_philo == 1)
			data->philo[i].m_fork_right = NULL;
		data->philo[i].data = data;
		++i;
	}
	return (0);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	pthread_mutex_lock(&philo->data->m_start);
	philo->time_last_meal = philo->data->t_t_start;
	pthread_mutex_unlock(&philo->data->m_start);
	if (philo->time_last_meal == -1)
		return (NULL);
	if (philo->id % 2 == 0)
		ft_usleep(philo, (philo->data->t_t_e * 0.9));
	while (is_end(philo->data) == 0)
	{
		if (ft_eat(philo))
			break ;
		ft_print(philo, "is sleeping");
		if (ft_usleep(philo, philo->data->t_t_s))
			break ;
		ft_print(philo, "is thinking");
	}
	philo->n_meal = -1;
	return (NULL);
}

int	philo_create(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->m_start);
	while (i < data->n_philo)
	{
		if (pthread_create(&data->philo[i].id_thread, NULL, &routine, \
			&data->philo[i]))
		{
			printf("Error : philo %d creation failed\n", data->philo[i].id);
			break ;
		}
		++i;
	}
	data->t_t_start = get_time();
	pthread_mutex_unlock(&data->m_start);
	if (i != data->n_philo)
		return (1);
	return (0);
}
