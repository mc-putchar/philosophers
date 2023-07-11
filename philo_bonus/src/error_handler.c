/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 08:03:29 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/11 14:26:47 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	destroy_semaphores(t_data *d)
{
	(void)sem_close(d->sync);
	(void)sem_close(d->forks);
	(void)sem_close(d->eating_q);
	(void)sem_close(d->write);
	(void)sem_close(d->stop_sim);
	(void)sem_close(d->phullo);
	(void)sem_unlink("sync");
	(void)sem_unlink("forks");
	(void)sem_unlink("eating_q");
	(void)sem_unlink("write");
	(void)sem_unlink("stop_sim");
	(void)sem_unlink("phullo");
	return (0);
}

int	error_handler(char *msg, int (*f)(), void *arg)
{
	write(STDERR_FILENO, "\033[31m./philo_bonus ", 19);
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\033[0m", 4);
	if (f)
		f(arg);
	return (EXIT_FAILURE);
}
