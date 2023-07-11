/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 05:04:49 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/11 15:06:30 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static char	*get_sem_name(char *name, int i)
{
	char	*sem_name;
	char	*tmp;

	tmp = ft_itoa(i);
	sem_name = ft_strjoin(name, tmp);
	free(tmp);
	if (!sem_name)
		exit(error_handler("Error: malloc failed\n", NULL, NULL));
	return (sem_name);
}

void	philo_life(t_philo *p)
{
	char const	*sem_name = get_sem_name("/philo", p->id);

	(void)sem_unlink(sem_name);
	p->dead = sem_open(sem_name, O_CREAT | O_EXCL, 0700, 0);
	sem_unlink(sem_name);
	free((void *)sem_name);
	if (p->dead == SEM_FAILED)
		exit(error_handler("Error: sem_open failed\n", NULL, NULL));
	if (pthread_create(&p->reaper, NULL, nega_philo, p))
		exit(error_handler("Error: nega thread failed\n", \
		sem_close, p->dead));
	sem_wait(p->data->sync);
	gettimeofday(&p->last_meal, NULL);
	sem_post(p->dead);
	while (1)
		if (philo_eat(p) || philo_sleep(p) || philo_think(p))
			break ;
	pthread_join(p->reaper, NULL);
	exit(sem_close(p->dead));
}

void	*nega_philo(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (1)
	{
		sem_wait(p->dead);
		if (get_elapsed_time(p->last_meal) > p->data->time_to_die)
		{
			(void)philo_die(p);
			return (NULL);
		}
		else
			sem_post(p->dead);
		ft_sleepms(1);
	}
	return (NULL);
}
