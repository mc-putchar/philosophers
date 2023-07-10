/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 05:30:37 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/10 13:02:16 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	philo_forks(t_philo *p)
{
	sem_wait(p->data->forks);
	if (status_log(p, C_FORK))
		return (sem_post(p->data->forks), 1);
	sem_wait(p->data->forks);
	if (status_log(p, C_FORK))
		return (sem_post(p->data->forks), sem_post(p->data->forks), 1);
	return (0);
}

int	philo_eat(t_philo *p)
{
	if (philo_forks(p))
		return (1);
	sem_wait(p->eat);
	if (status_log(p, C_EAT))
		return (1);
	if (gettimeofday(&p->last_meal, NULL))
		return (error_handler("Error: gettimeofday failed\n", NULL, NULL));
	p->meals++;
	p->status = EATS;
	sem_post(p->eat);
	ft_sleepms(p->data->time_to_eat);
	sem_post(p->data->forks);
	sem_post(p->data->forks);
	if (p->meals == p->data->meals)
		sem_post(p->data->phullo);
	// if (philo_sleep(p))
	// 	return (1);
	return (0);
}

// int	philo_sleep(t_philo *p)
// {
// 	if (status_log(p, C_SLEEP))
// 		return (1);
// 	ft_sleepms(p->data->time_to_sleep);
// 	return (0);
// }

int	philo_think(t_philo *p)
{
	if (status_log(p, C_THINK))
		return (1);
	ft_sleepms(p->data->time_to_think);
	return (0);
}

int	philo_die(t_philo *p)
{
	(void)status_log(p, C_DIE);
	(void)sem_post(p->data->bad_news);
	(void)sem_wait(p->data->write);
	return (0);
}
