/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_log.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:01:30 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/11 14:17:02 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	status_log(t_philo *p, char *msg)
{
	int	time;

	if (sem_wait(p->data->write))
		return (error_handler("Error: sem_wait failed\n", NULL, NULL));
	if (p->data->sim_end)
		return (sem_post(p->data->write), 1);
	time = get_elapsed_time(p->data->start);
	printf(PRINT_FORMAT, time, p->id, msg);
	if (sem_post(p->data->write))
		return (error_handler("Error: sem_post failed\n", NULL, NULL));
	return (0);
}
