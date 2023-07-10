/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 07:58:57 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/10 04:54:48 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_elapsed_time(struct timeval start)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL))
		return (error_handler("Error: gettimeofday", NULL, NULL), -1);
	return ((now.tv_sec - start.tv_sec) * 1000 \
	+ (now.tv_usec - start.tv_usec) / 1000);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	diff;

	diff = 0;
	while (!diff && n-- && (*s1 || *s2))
		diff = (unsigned char) *s1++ - (unsigned char) *s2++;
	return (diff);
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		++len;
	return (len);
}

void	ft_memset(void *ptr, int c, size_t len)
{
	unsigned char	*mem;

	mem = (unsigned char *)ptr;
	while (len--)
		*mem++ = (unsigned char)c;
}
