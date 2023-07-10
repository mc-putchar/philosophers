/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_log.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:01:30 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/10 01:42:29 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	status_log(t_philo *p, char *msg)
{
	int	time;

	pthread_mutex_lock(&p->data->bad_news);
	if (p->data->sim_end)
		return (pthread_mutex_unlock(&p->data->bad_news), 1);
	pthread_mutex_unlock(&p->data->bad_news);
	pthread_mutex_lock(&p->data->write);
	time = get_elapsed_time(p->data->start);
	printf(PRINT_FORMAT, time, p->id, msg);
	pthread_mutex_unlock(&p->data->write);
	return (0);
}
