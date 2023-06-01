/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:57:10 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/06/01 13:08:10 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *str)
{
	long int	res;
	int			sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		str++;
	}
	return ((int) sign * res);
}

int	parser_error(int err)
{
	if (err == 1)
		printf(ARGS_ERROR);
	else if (err == 2)
		printf("Error : too much arg\n");
	else if (err == 3)
		printf("Error : negative value are not possible...\n");
	else if (err == 4)
		printf("Error : mutex_init failed\n");
	return (1);
}

static int	check_arg(t_data *data)
{
	if (data->n_philo < 0)
		return (1);
	if (data->t_t_d < 0)
		return (1);
	if (data->t_t_e < 0)
		return (1);
	if (data->t_t_s < 0)
		return (1);
	return (0);
}

int	parser(int ac, char **arg, t_data *data)
{
	data->n_philo = ft_atoi(arg[1]);
	data->t_t_d = ft_atoi(arg[2]);
	data->t_t_e = ft_atoi(arg[3]);
	data->t_t_s = ft_atoi(arg[4]);
	data->t_t_pause = data->n_philo * 10;
	if (check_arg(data))
		return (parser_error(3));
	if (ac == 6)
	{
		data->n_meal = ft_atoi(arg[5]);
		if (data->n_meal < 0)
			return (parser_error(3));
	}
	else
		data->n_meal = -2;
	data->dead = 0;
	if (pthread_mutex_init(&data->reaper, NULL))
		return (parser_error(4));
	if (pthread_mutex_init(&data->m_start, NULL))
	{
		pthread_mutex_destroy(&data->reaper);
		return (parser_error(4));
	}
	return (0);
}
