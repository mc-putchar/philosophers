/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 04:20:48 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/10 07:40:24 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semaphores(t_data *d)
{
	(void)sem_unlink("forks");
	(void)sem_unlink("write");
	(void)sem_unlink("bad_news");
	d->forks = sem_open("forks", O_CREAT, 0644, d->philo_n);
	d->write = sem_open("write", O_CREAT, 0644, 1);
	d->bad_news = sem_open("bad_news", O_CREAT, 0644, 0);
	if (d->forks == SEM_FAILED || d->write == SEM_FAILED
		|| d->bad_news == SEM_FAILED)
		return (error_handler("Error: sem_open failed\n", \
			destroy_semaphores, d));
	return (0);
}

int	destroy_semaphores(t_data *d)
{
	(void)sem_close(d->forks);
	(void)sem_close(d->write);
	(void)sem_close(d->bad_news);
	(void)sem_unlink("forks");
	(void)sem_unlink("write");
	(void)sem_unlink("bad_news");
	return (0);
}

int	free_philos(t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->philo_n)
	{
		(void)sem_close(d->philo[i].philosem);
		(void)sem_unlink("philosem");
	}
	free(d->philo);
	return (0);
}

int	init_philos(t_data *d)
{
	int	i;

	d->philo = malloc(sizeof(t_philo) * d->philo_n);
	if (!d->philo)
		return (error_handler(strerror(errno), destroy_semaphores, d));
	i = -1;
	while (++i < d->philo_n)
	{
		d->philo[i].id = i + 1;
		d->philo[i].data = d;
		d->philo[i].meals = 0;
		(void)sem_unlink("philosem");
		d->philo[i].philosem = sem_open("philosem", O_CREAT, 0644, 1);
		if (d->philo[i].philosem == SEM_FAILED)
			return (error_handler("Error: sem_open failed\n", NULL, NULL));
		d->philo[i].pid = fork();
		if (d->philo[i].pid < 0)
			return (error_handler("Error: fork failed\n", NULL, NULL));
		if (!d->philo[i].pid)
			philo_life(&d->philo[i]);
	}
	return (0);
}

int	init_data(t_data *data, int ac, char **av)
{
	data->philo_n = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);	
	data->time_to_sleep = ft_atoi(av[4]);
	data->meals = 0;
	if (ac == 6)
		data->meals = ft_atoi(av[5]);
	if (data->philo_n < 1 || data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1 || (ac == 6 && data->meals < 1))
		return (error_handler("Error: invalid arguments\n", NULL, NULL));
	if (gettimeofday(&data->start, NULL))
		return (error_handler("Error: gettimeofday failed\n", NULL, NULL));
	if (init_semaphores(data) || init_philos(data))
		return (EXIT_FAILURE);
	return (0);
}
