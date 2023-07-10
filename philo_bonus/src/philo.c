/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 05:04:49 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/10 07:54:50 by mcutura          ###   ########.fr       */
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
		if (sem_wait(p->philosem))
				return (error_handler("Error: sem_wait\n", NULL, NULL), NULL);
		if (get_elapsed_time(p->last_meal) > p->data->time_to_die)
		{
			if (philo_die(p))
				return (NULL);
			if (sem_post(p->philosem))
				(void)error_handler("Error: sem_post\n", NULL, NULL);
			return (NULL);
		}
		if (p->meals == p->data->meals)
			sem_post(p->data->phullo);
		if (sem_post(p->philosem))
			return (error_handler("Error: sem_post\n", NULL, NULL), NULL);
	}
}

int	han_solo(t_philo *p)
{
	sem_wait(p->data->forks);
	status_log(p, C_FORK);
	ft_sleepms(p->data->time_to_die);
	philo_die(p);
	sem_post(p->data->forks);
	return (0);
}

void	philo_life(t_philo	*p)
{
	pthread_t	nega;

	p->status = READY;
	p->last_meal = p->data->start;
	if (p->data->philo_n == 1)
		exit(han_solo(p));
	if (pthread_create(&nega, NULL, nega_philo, p))
		exit(error_handler("Error: pthread_create\n", NULL, NULL));
	pthread_detach(nega);
	if (!(p->id & 1))
		ft_sleepms(p->data->time_to_eat - 1);
	while (1)
	{
		if (philo_eat(p))
			exit(0);
		if (philo_sleep(p))
			exit(0);
		if (philo_think(p))
			exit(0);
	}
}
