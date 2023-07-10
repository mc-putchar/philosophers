/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleepms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 02:06:41 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/10 08:19:01 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sleepms(int ms)
{
	struct timeval	start;

	if (ms <= 0)
		return ;
	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(500);
		if (get_elapsed_time(start) >= ms)
			return ;
	}
}
