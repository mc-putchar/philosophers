/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 02:54:59 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/10 02:38:26 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_data *data)
{
	int	i;

	if (pthread_join(data->grim_reaper, NULL))
		return (error_handler("Error: reaper thread_join\n", NULL, NULL));
	i = -1;
	while (++i < data->philo_n)
		if (pthread_join(data->philo[i].thread, NULL))
			return (error_handler("Error: philo pthread_join\n", NULL, NULL));
	return (EXIT_SUCCESS);
}

int	main(int ac, const char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (printf("%s\n", USAGE), EXIT_SUCCESS);
	if (uint_check((char **)av + 1))
		return (error_handler("Error: invalid arguments\n", NULL, NULL));
	if (init_data(&data, ac, av))
		return (EXIT_FAILURE);
	if (init_threads(&data))
		return (EXIT_FAILURE);
	if (join_threads(&data))
		return (EXIT_FAILURE);
	(void)free_data(&data);
	return (EXIT_SUCCESS);
}

int	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_n)
	{
		if (pthread_mutex_destroy(&data->philo[i].right_fork))
			(void)error_handler("Error: fork mutex_destroy:\n", NULL, NULL);
		if (pthread_mutex_destroy(&data->philo[i].hunger))
			(void)error_handler("Error: hunger mutex_destroy\n", NULL, NULL);
	}
	if (pthread_mutex_destroy(&data->write))
		(void)error_handler("Error: write mutex_destroy\n", NULL, NULL);
	if (pthread_mutex_destroy(&data->bad_news))
		(void)error_handler("Error: end mutex_destroy\n", NULL, NULL);
	free(data->philo);
	return (EXIT_SUCCESS);
}
