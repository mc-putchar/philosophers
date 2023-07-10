/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 03:58:45 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/10 13:51:40 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*monitor_meals(void *data)
{
	t_data	*d;
	int		i;

	d = (t_data *)data;
	i = -1;
	while (++i < d->philo_n)
		sem_wait(d->phullo);
	sem_post(d->bad_news);
	return (NULL);
}

static int	give_life(t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->philo_n)
	{
		d->philo[i].pid = fork();
		if (d->philo[i].pid == -1)
			return (error_handler("Error: fork failed\n", shred_data, d));
		if (!d->philo[i].pid)
			philo_life(&d->philo[i]);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data		data;
	int			i;
	pthread_t	monitor;

	if (ac < 5 || ac > 6)
		return (printf("%s\n", USAGE), EXIT_SUCCESS);
	if (uint_check(av + 1))
		return (error_handler("Error: invalid arguments\n", NULL, NULL));
	if (init_data(&data, ac, av))
		return (EXIT_FAILURE);
	pthread_create(&monitor, NULL, monitor_meals, &data);
	// pthread_detach(monitor);
	if (give_life(&data))
		return (EXIT_FAILURE);
	i = -1;
	sem_wait(data.bad_news);
	while (++i < data.philo_n)
		kill(data.philo[i].pid, SIGKILL);
	return (shred_data(&data), 0);
}