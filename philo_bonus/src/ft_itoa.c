/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:48:40 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/11 14:03:13 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_intlen(int n)
{
	int		len;

	len = 1;
	if (n < 0)
		++len;
	while (n && ++len)
		n /= 10;
	return (len);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*cpy;

	len = ft_strlen(s);
	cpy = malloc(len + 1);
	if (!cpy)
		return (NULL);
	cpy[len] = 0;
	while (len--)
		cpy[len] = s[len];
	return (cpy);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		neg;

	if (!n)
		return (ft_strdup("0"));
	len = ft_intlen(n);
	str = malloc(len);
	if (!str)
		return (NULL);
	str[--len] = '\0';
	neg = 1;
	if (n < 0)
		neg = -1;
	while (n)
	{
		str[--len] = (n % 10) * neg + '0';
		n /= 10;
	}
	if (neg == -1)
		str[0] = '-';
	return (str);
}
