/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 06:22:59 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/10 02:45:01 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	inspect_philo(t_philo *p, int *phull)
{
	static int	full_philos = 0;

	if (is_dead(p))
		return (1);
	pthread_mutex_lock(&p->hunger);
	if (p->status == FULL)
	{
		full_philos++;
		*phull = FULL;
	}
	pthread_mutex_unlock(&p->hunger);
	if (full_philos == p->data->philo_n)
	{
		pthread_mutex_lock(&p->data->bad_news);
		p->data->sim_end = 1;
		pthread_mutex_unlock(&p->data->bad_news);
		return (1);
	}
	return (0);
}

void	*grim_reaper(void *data)
{
	t_data	*d;
	int		i;
	int		*phull;

	d = (t_data *)data;
	if (d->philo_n == 1)
		return (NULL);
	ft_sleepms(d->time_to_die - 1);
	phull = ft_calloc(d->philo_n, sizeof(int));
	if (!phull)
		return (NULL);
	while (1)
	{
		i = -1;
		while (++i < d->philo_n)
		{
			if (phull[i] != FULL && inspect_philo(&d->philo[i], phull + i))
				return (free(phull), NULL);
		}
	}
}
