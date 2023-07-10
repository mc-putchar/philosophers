/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 08:03:29 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/10 05:45:59 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	error_handler(char *msg, int (*f)(), void *arg)
{
	write(STDERR_FILENO, "\033[31m./philo_bonus ", 13);
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\033[0m", 4);
	if (f)
		f(arg);
	return (EXIT_FAILURE);
}
