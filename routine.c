/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:57:44 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/06/01 14:34:54 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(t_philo *philo, long int duration)
{
	long int	end_time;

	end_time = get_time() + duration;
	if (end_time == -1)
		return (-1);
	while (get_time() < end_time)
	{
		if (is_end(philo->data) || ft_died(philo))
			return (1);
		usleep(philo->data->t_t_pause * 2);
	}
	return (0);
}

void	ft_take_fork(pthread_mutex_t *m_fork, t_philo *p, int *fork, int *i)
{
	pthread_mutex_lock(m_fork);
	if (*fork == 0)
	{
		*fork = p->id;
		--(*i);
		ft_print(p, "has taken a fork");
	}
	pthread_mutex_unlock(m_fork);
}

int	ft_try_fork(t_philo *philo)
{
	pthread_mutex_t	*m_fork[2];
	int				i;

	m_fork[0] = &philo->m_fork_left;
	m_fork[1] = philo->m_fork_right;
	i = 2;
	while (i)
	{
		ft_take_fork(m_fork[0], philo, &philo->fork_left, &i);
		if (m_fork[1])
			ft_take_fork(m_fork[1], philo, philo->fork_right, &i);
		if (ft_died(philo) || is_end(philo->data))
			return (1);
		usleep(philo->data->t_t_pause);
	}
	return (0);
}

int	ft_give_back_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_fork_left);
	philo->fork_left = 0;
	pthread_mutex_unlock(&philo->m_fork_left);
	pthread_mutex_lock(philo->m_fork_right);
	*philo->fork_right = 0;
	pthread_mutex_unlock(philo->m_fork_right);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	if (ft_try_fork(philo))
		return (1);
	philo->time_last_meal = get_time();
	ft_print(philo, "is eating");
	++philo->n_meal;
	if (philo->n_meal == philo->data->n_meal)
	{
		pthread_mutex_lock(&philo->data->reaper);
		++philo->data->dead;
		pthread_mutex_unlock(&philo->data->reaper);
	}
	if (ft_usleep(philo, philo->data->t_t_e))
	{
		ft_give_back_fork(philo);
		return (1);
	}
	ft_give_back_fork(philo);
	if (is_end(philo->data))
		return (1);
	return (0);
}
