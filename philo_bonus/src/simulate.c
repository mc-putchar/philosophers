/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:29:08 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/11 14:31:01 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philler(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = -1;
	while (++i < data->philo_n)
		sem_wait(data->phullo);
	sem_wait(data->sync);
	data->sim_end = 1;
	sem_post(data->sync);
	sem_post(data->stop_sim);
	exit(0);
}

static void	cleanup(t_data *data, pid_t *pids)
{
	int	i;

	i = -1;
	kill(data->philler, SIGKILL);
	while (++i < data->philo_n)
		kill(pids[i], SIGKILL);
	destroy_semaphores(data);
}

int	simulate(t_data *data, pid_t *pids)
{
	int	i;

	i = -1;
	data->philler = fork();
	if (data->philler == -1)
		return (error_handler("Error: philler fork\n", NULL, NULL));
	if (!data->philler)
		philler(data);
	gettimeofday(&data->start, NULL);
	while (++i < data->philo_n)
		sem_post(data->sync);
	sem_post(data->sync);
	sem_wait(data->stop_sim);
	cleanup(data, pids);
	return (0);
}
