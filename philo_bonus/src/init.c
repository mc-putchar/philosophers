/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 04:20:48 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/11 15:06:43 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_data(t_data *d, int ac, char **av)
{
	d->sim_end = 0;
	d->phullos = 0;
	d->philo_n = ft_atoi(av[1]);
	d->time_to_die = ft_atoi(av[2]);
	d->time_to_eat = ft_atoi(av[3]);
	d->time_to_sleep = ft_atoi(av[4]);
	d->meals_fill = -1;
	if (ac == 6)
		d->meals_fill = ft_atoi(av[5]);
	if (d->philo_n < 1 || d->time_to_die < 1 || d->time_to_eat < 1 \
		|| d->time_to_sleep < 1 || (ac == 6 && d->meals_fill < 1))
		return (error_handler("Error: invalid arguments\n", NULL, NULL));
	if (d->philo_n > 250)
		return (error_handler("Error: too many philosophers\n", NULL, NULL));
	if (gettimeofday(&d->start, NULL))
		return (error_handler("Error: gettimeofday failed\n", NULL, NULL));
	return (0);
}

int	init_semaphores(t_data *d)
{
	(void)sem_unlink("sync");
	(void)sem_unlink("forks");
	(void)sem_unlink("eating_q");
	(void)sem_unlink("write");
	(void)sem_unlink("phullo");
	(void)sem_unlink("stop_sim");
	d->sync = sem_open("sync", O_CREAT, 0644, 0);
	d->forks = sem_open("forks", O_CREAT, 0644, d->philo_n);
	d->eating_q = sem_open("eating_q", O_CREAT, 0644, (d->philo_n / 2) + 1);
	d->write = sem_open("write", O_CREAT, 0644, 1);
	d->phullo = sem_open("phullo", O_CREAT, 0644, 0);
	d->stop_sim = sem_open("stop_sim", O_CREAT, 0644, 0);
	if (d->forks == SEM_FAILED || d->write == SEM_FAILED \
		|| d->phullo == SEM_FAILED || d->stop_sim == SEM_FAILED \
		|| d->eating_q == SEM_FAILED || d->sync == SEM_FAILED)
		return (error_handler("Error: sem_open failed\n", \
			destroy_semaphores, d));
	return (0);
}

int	init_philos(t_data *d, pid_t *pids)
{
	t_philo	philo;
	int		i;

	i = -1;
	while (++i < d->philo_n)
	{
		philo.id = i + 1;
		philo.meals = 0;
		philo.data = d;
		pids[i] = fork();
		if (pids[i] == -1)
			return (error_handler("Error: fork failed\n", \
				NULL, NULL));
		if (!pids[i])
			philo_life(&philo);
	}
	return (0);
}
