/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:51:13 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/11 13:54:29 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	i;

	srclen = ft_strlen(src);
	if (size && src && dst)
	{
		if (size > srclen)
			size = srclen + 1;
		i = 0;
		while (i < size - 1)
		{
			dst[i] = src[i];
			++i;
		}
		dst[i] = 0;
	}
	return (srclen);
}

static size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	i;

	srclen = ft_strlen(src);
	dstlen = 0;
	while (dst[dstlen] && dstlen < size)
		++dstlen;
	i = 0;
	if (srclen && size)
	{
		while (*src && i + dstlen < size - 1)
		{
			dst[dstlen + i] = *src++;
			++i;
		}
	}
	if (dstlen + i < size)
		dst[dstlen + i] = 0;
	return (dstlen + srclen);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*joined;
	size_t	len;

	if (!*s2)
		return (ft_strdup(s1));
	if (!*s1)
		return (ft_strdup(s2));
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = malloc(len);
	if (!joined)
		return (NULL);
	(void)ft_strlcpy(joined, s1, len);
	(void)ft_strlcat(joined, s2, len);
	return (joined);
}
