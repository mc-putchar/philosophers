/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 22:38:51 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/01 02:03:02 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	uint_check(char **tab)
{
	int		i;
	int		j;

	i = -1;
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j] && j < 10)
			if (!ft_isdigit(tab[i][j]))
				return (EXIT_FAILURE);
		if (j == 10 && ft_strncmp(tab[i], MAX_INT_S, 10) > 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
