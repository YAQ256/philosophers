/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 07:04:33 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/06/01 14:55:53 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clear_all(t_data *data)
{
	while (--data->n_philo > 0)
		pthread_mutex_destroy(&data->philo[data->n_philo].m_fork_left);
	free(data->philo);
	pthread_mutex_destroy(&data->reaper);
}

int	main(int ac, char **arg)
{
	t_data	data;
	int		i;

	if (ac < 5)
		return (parser_error(1));
	if (ac > 6)
		return (parser_error(2));
	if (parser(ac, arg, &data))
		return (1);
	if (data.n_philo == 0)
		return (0);
	if (philo_init(&data))
		return (1);
	i = philo_create(&data);
	if (i)
		data.n_philo = i;
	i = 0;
	while (i < data.n_philo)
	{
		pthread_join(data.philo[i].id_thread, NULL);
		++i;
	}
	clear_all(&data);
	return (0);
}