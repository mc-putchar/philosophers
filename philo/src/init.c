/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 08:12:43 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/10 02:44:20 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->write, NULL))
		return (error_handler(strerror(errno), NULL, NULL));
	if (pthread_mutex_init(&data->bad_news, NULL))
	{
		pthread_mutex_destroy(&data->write);
		return (error_handler(strerror(errno), NULL, NULL));
	}
	data->philo = malloc(sizeof(t_philo) * data->philo_n);
	if (!data->philo || init_philo(data))
	{
		pthread_mutex_destroy(&data->write);
		pthread_mutex_destroy(&data->bad_news);
		return (error_handler("Error: failed to init philos\n", NULL, NULL));
	}
	return (EXIT_SUCCESS);
}

int	init_data(t_data *data, int ac, const char **av)
{
	ft_memset(data, 0, sizeof(t_data));
	data->philo_n = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->time_to_think = TIME_TO_THINK;
	if (data->philo_n & 1 && data->philo_n > 1 && \
		data->time_to_eat * 2 > data->time_to_sleep)
		data->time_to_think = data->time_to_eat * 2 - data->time_to_sleep;
	data->sim_end = 0;
	data->meals = 0;
	if (ac == 6)
		data->meals = ft_atoi(av[5]);
	if (data->philo_n < 1 || data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1 || (ac == 6 && data->meals < 1))
		return (error_handler("Error: invalid arguments\n", NULL, NULL));
	if (init_mutexes(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_n)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meals = 0;
		data->philo[i].data = data;
		data->philo[i].status = READY;
		if (pthread_mutex_init(&data->philo[i].right_fork, NULL) || \
			pthread_mutex_init(&data->philo[i].hunger, NULL))
		{
			data->philo_n = i;
			return (error_handler(strerror(errno), free_data, data));
		}
		if (i)
			data->philo[i].left_fork = &data->philo[i - 1].right_fork;
	}
	if (data->philo_n > 1)
		data->philo[0].left_fork = &data->philo[data->philo_n - 1].right_fork;
	else
		data->philo[0].left_fork = NULL;
	return (EXIT_SUCCESS);
}

int	init_threads(t_data *data)
{
	int	i;

	if (gettimeofday(&data->start, NULL))
		return (error_handler("Error: gettimeofday failed\n", \
		free_data, data));
	if (pthread_create(&data->grim_reaper, NULL, &grim_reaper, data))
		return (error_handler("Error: failed to init reaper\n", \
		free_data, data));
	i = -1;
	while (++i < data->philo_n)
	{
		if (pthread_create(&data->philo[i].thread, NULL, \
		&philo_life, &data->philo[i]))
			return (error_handler("Error: pthread_create failed\n", \
			free_data, data));
	}
	return (EXIT_SUCCESS);
}
