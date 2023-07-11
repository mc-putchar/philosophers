/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 05:30:37 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/11 14:23:38 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	philo_forks(t_philo *p)
{
	sem_wait(p->data->eating_q);
	sem_wait(p->data->forks);
	if (status_log(p, C_FORK))
	{
		sem_post(p->data->eating_q);
		return (sem_post(p->data->forks), 1);
	}
	sem_wait(p->data->forks);
	if (status_log(p, C_FORK))
	{
		sem_post(p->data->eating_q);
		return (sem_post(p->data->forks), sem_post(p->data->forks), 1);
	}
	sem_post(p->data->eating_q);
	return (0);
}

int	philo_eat(t_philo *p)
{
	if (philo_forks(p))
		return (1);
	sem_wait(p->dead);
	if (gettimeofday(&p->last_meal, NULL))
		return (error_handler("Error: gettimeofday failed\n", \
		sem_post, p->dead));
	sem_post(p->dead);
	if (status_log(p, C_EAT))
		return (1);
	if (++p->meals == p->data->meals_fill)
		sem_post(p->data->phullo);
	ft_sleepms(p->data->time_to_eat);
	sem_post(p->data->forks);
	sem_post(p->data->forks);
	return (0);
}

int	philo_sleep(t_philo *p)
{
	if (status_log(p, C_SLEEP))
		return (1);
	ft_sleepms(p->data->time_to_sleep);
	return (0);
}

int	philo_think(t_philo *p)
{
	if (status_log(p, C_THINK))
		return (1);
	ft_sleepms(0);
	return (0);
}

int	philo_die(t_philo *p)
{
	(void)status_log(p, C_DIE);
	p->data->sim_end = 1;
	(void)sem_post(p->data->stop_sim);
	return (0);
}
