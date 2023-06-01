/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 06:25:31 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/06/01 13:22:43 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>

# define ARGS_ERROR "./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

typedef struct s_philo
{
	int				id;
	pthread_t		id_thread;
	long int		time_last_meal;
	int				n_meal;
	pthread_mutex_t	m_fork_left;
	pthread_mutex_t	*m_fork_right;
	int				fork_left;
	int				*fork_right;
	struct s_data	*data;

}	t_philo;

typedef struct s_data
{
	t_philo			*philo;
	int				n_philo;
	long int		t_t_d;
	long int		t_t_e;
	long int		t_t_s;
	long int		t_t_start;
	long int		t_t_pause;
	int				n_meal;
	pthread_mutex_t	reaper;
	pthread_mutex_t	m_start;
	int				dead;
}	t_data;

int			parser(int ac, char **arg, t_data *data);
int			parser_error(int err);
int			philo_init(t_data *data);
int			philo_create(t_data *data);

long int	get_time(void);
int			is_end(t_data *data);
void		ft_print(t_philo *philo, char *str);

int			ft_usleep(t_philo *philo, long int duration);
int			ft_eat(t_philo *philo);
int			ft_died(t_philo *philo);

#endif