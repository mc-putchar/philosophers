/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 03:58:45 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/10 07:56:23 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*phull_counter_f(void *arg)
{
	t_data	*data;
	int		phull;

	data = (t_data *)arg;
	phull = -1;
	while (++phull < data->philo_n)
		sem_wait(data->phullo);
	sem_post(data->bad_news);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data		data;
	int			i;
	pthread_t	phull_counter;

	if (ac < 5 || ac > 6)
		return (printf("%s\n", USAGE), EXIT_SUCCESS);
	if (uint_check(av + 1))
		return (error_handler("Error: invalid arguments\n", NULL, NULL));
	if (init_data(&data, ac, av))
		return (EXIT_FAILURE);
	if (pthread_create(&phull_counter, NULL, &phull_counter_f, &data))
		return (error_handler("Error: pthread_create failed\n", \
			destroy_semaphores, &data));
	sem_wait(data.bad_news);
	i = -1;
	while (++i < data.philo_n)
		kill(data.philo[i].pid, SIGKILL);
	(void)pthread_join(phull_counter, NULL);
	return (0);
}