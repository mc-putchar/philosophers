/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 03:58:45 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/11 15:06:49 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;
	pid_t	pids[250];

	if (ac == 1)
		return (printf(USAGE), 0);
	if (ac < 5 || ac > 6)
		return (error_handler("Error: wrong number of arguments\n", \
			NULL, NULL));
	if (uint_check(av + 1))
		return (error_handler("Error: invalid arguments\n", NULL, NULL));
	if (init_data(&data, ac, av))
		return (1);
	if (init_semaphores(&data))
		return (1);
	if (init_philos(&data, pids))
		return (1);
	if (simulate(&data, pids))
		return (1);
	return (0);
}
