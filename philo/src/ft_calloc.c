/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 00:06:49 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/10 03:14:11 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline static void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*(unsigned char *)s++ = 0;
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	int		i;

	if (!nmemb || !size)
		return (malloc(0));
	if (INT_MAX / nmemb < size)
	{
		errno = ENOMEM;
		return (NULL);
	}
	i = nmemb * size;
	p = malloc(i);
	if (!p)
		return (NULL);
	ft_bzero(p, i);
	return (p);
}
