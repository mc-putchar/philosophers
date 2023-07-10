/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 08:03:29 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/10 03:18:50 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_handler(char *str, int (*f)(), void *arg)
{
	write(STDERR_FILENO, "\033[31m./philo ", 13);
	if (str)
		write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\033[0m", 4);
	if (f)
		f(arg);
	return (EXIT_FAILURE);
}
