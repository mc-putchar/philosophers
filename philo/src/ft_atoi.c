/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 23:45:27 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/10 00:26:13 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline static int	ft_isspace(int c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

int	ft_atoi(const char *nptr)
{
	int	res;
	int	neg;

	neg = 1;
	res = 0;
	while (ft_isspace(*nptr))
		++nptr;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			neg = -1;
	while (ft_isdigit(*nptr))
		res = res * 10 + (*nptr++ - '0');
	return (res * neg);
}
