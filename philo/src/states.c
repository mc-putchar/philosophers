/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 23:58:54 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/10 02:41:16 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	forking(t_philo *p)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (p->id & 1)
	{
		first_fork = p->left_fork;
		second_fork = &p->right_fork;
	}
	else
	{
		first_fork = &p->right_fork;
		second_fork = p->left_fork;
	}
	pthread_mutex_lock(first_fork);
	if (status_log(p, C_FORK))
		return (pthread_mutex_unlock(first_fork), 1);
	pthread_mutex_lock(second_fork);
	if (status_log(p, C_FORK))
		return (pthread_mutex_unlock(first_fork), \
			pthread_mutex_unlock(second_fork), 1);
	return (0);
}

int	eating(t_philo *p)
{
	pthread_mutex_lock(&p->hunger);
	p->status = EATS;
	p->meals++;
	gettimeofday(&p->last_meal, NULL);
	pthread_mutex_unlock(&p->hunger);
	if (status_log(p, C_EAT))
		return (1);
	ft_sleepms(p->data->time_to_eat);
	if (p->id & 1)
	{
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(&p->right_fork);
	}
	else
	{
		pthread_mutex_unlock(&p->right_fork);
		pthread_mutex_unlock(p->left_fork);
	}
	return (0);
}

int	sleeping(t_philo *p)
{
	if (status_log(p, C_SLEEP))
		return (1);
	ft_sleepms(p->data->time_to_sleep);
	return (0);
}

int	thinking(t_philo *p)
{
	if (status_log(p, C_THINK))
		return (1);
	ft_sleepms(p->data->time_to_think);
	return (0);
}

int	is_dead(t_philo *p)
{
	int	time;

	pthread_mutex_lock(&p->hunger);
	time = get_elapsed_time(p->last_meal);
	pthread_mutex_unlock(&p->hunger);
	if (time > p->data->time_to_die)
	{
		(void)status_log(p, C_DIE);
		pthread_mutex_lock(&p->data->bad_news);
		p->data->sim_end = 1;
		pthread_mutex_unlock(&p->data->bad_news);
		return (1);
	}
	return (0);
}
