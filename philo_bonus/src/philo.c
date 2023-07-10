/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 05:04:49 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/10 15:05:46 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*nega_philo(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	ft_sleepms(p->data->time_to_die);
	while (1)
	{
		sem_wait(p->eat);
		if (get_elapsed_time(p->last_meal) > p->data->time_to_die)
			exit(philo_die(p));
		else
			sem_post(p->eat);
		ft_sleepms(1);
	}
}

static int	han_solo_dies(t_philo *p)
{
	(void)sem_wait(p->data->forks);
	(void)status_log(p, C_FORK);
	ft_sleepms(p->data->time_to_die);
	(void)philo_die(p);
	(void)sem_post(p->data->forks);
	return (shred_data(p->data));
}

void	philo_life(t_philo	*p)
{
	p->status = READY;
	(void)sem_unlink("eat");
	p->eat = sem_open("eat", O_CREAT, 0644, 1);
	if (p->eat == SEM_FAILED)
		exit(error_handler("Error: sem_open failed\n", shred_data, p->data));
	gettimeofday(&p->start, NULL);
	p->last_meal = p->start;
	if (p->data->philo_n == 1)
		exit(han_solo_dies(p));
	if (pthread_create(&p->reaper, NULL, nega_philo, p))
		exit(error_handler("Error: pthread_create\n", shred_data, p->data));
	pthread_detach(p->reaper);
	if (!(p->id & 1))
		ft_sleepms(p->data->time_to_eat - 1);
	while (1)
	{
		if (philo_eat(p))
			exit(shred_data(p->data));
		if (status_log(p, C_SLEEP))
			exit(shred_data(p->data));
		ft_sleepms(p->data->time_to_sleep);
		if (philo_think(p))
			exit(shred_data(p->data));
	}
}
