/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 08:53:45 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/10 03:21:03 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*solo_yolo(t_philo *p)
{
	(void)pthread_mutex_lock(&p->right_fork);
	(void)status_log(p, C_FORK);
	ft_sleepms(p->data->time_to_die);
	(void)pthread_mutex_unlock(&p->right_fork);
	(void)status_log(p, C_DIE);
	return (NULL);
}

static void	*every_day_is_exactly_the_same(t_philo *p)
{
	while (1)
	{
		if (forking(p) || eating(p))
			return (NULL);
		(void)pthread_mutex_lock(&p->hunger);
		if (p->data->meals && p->meals == p->data->meals)
		{
			p->status = FULL;
			return ((void)pthread_mutex_unlock(&p->hunger), NULL);
		}
		(void)pthread_mutex_unlock(&p->hunger);
		(void)pthread_mutex_lock(&p->data->bad_news);
		if (p->data->sim_end)
			return ((void)pthread_mutex_unlock(&p->data->bad_news), NULL);
		(void)pthread_mutex_unlock(&p->data->bad_news);
		if (sleeping(p))
			return (NULL);
		(void)pthread_mutex_lock(&p->data->bad_news);
		if (p->data->sim_end)
			return ((void)pthread_mutex_unlock(&p->data->bad_news), NULL);
		(void)pthread_mutex_unlock(&p->data->bad_news);
		if (thinking(p))
			return (NULL);
	}
}

void	*philo_life(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (p->data->philo_n == 1)
		return (solo_yolo(p));
	(void)pthread_mutex_lock(&p->hunger);
	p->last_meal = p->data->start;
	(void)pthread_mutex_unlock(&p->hunger);
	if (!(p->id & 1))
		ft_sleepms(p->data->time_to_eat - 1);
	return (every_day_is_exactly_the_same(p));
}
