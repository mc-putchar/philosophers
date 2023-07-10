/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 05:30:37 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/10 07:49:11 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	take_forks(t_philo *p)
{
	if (sem_wait(p->data->forks))
		return (error_handler("Error: sem_wait failed\n", NULL, NULL));
	if (status_log(p, C_FORK))
		return (sem_post(p->data->forks), 1);
	if (sem_wait(p->data->forks))
		return (error_handler("Error: sem_wait failed\n", NULL, NULL));
	if (status_log(p, C_FORK))
		return (sem_post(p->data->forks), sem_post(p->data->forks), 1);
	return (0);
}

int	philo_eat(t_philo *p)
{
	if (take_forks(p))
		return (1);
	if (sem_wait(p->philosem))
		return (error_handler("Error: sem_wait failed\n", NULL, NULL));
	if (gettimeofday(&p->last_meal, NULL))
		return (error_handler("Error: gettimeofday failed\n", NULL, NULL));
	p->status = EATS;
	p->meals++;
	if (status_log(p, C_EAT))
		return (1);
	if (sem_post(p->philosem))
		return (error_handler("Error: sem_post failed\n", NULL, NULL));
	ft_sleepms(p->data->time_to_eat);
	if (sem_post(p->data->forks) || sem_post(p->data->forks))
		return (error_handler("Error: sem_post failed\n", NULL, NULL));
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
	return (0);
}

int	philo_die(t_philo *p)
{
	p->status = DEAD;
	if (status_log(p, C_DIE))
		return (1);
	if (sem_post(p->data->bad_news))
		return (error_handler("Error: sem_post failed\n", NULL, NULL));
	return (0);
}
