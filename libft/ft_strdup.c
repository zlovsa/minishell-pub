/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:03:51 by mcarolee          #+#    #+#             */
/*   Updated: 2021/04/10 16:06:59 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*rv;
	long	l;

	if (!s)
		return (NULL);
	l = ft_strlen(s);
	rv = (char *)malloc(l + 1);
	if (rv)
		ft_memcpy(rv, s, l + 1);
	return (rv);
}

char	*ft_strndup(char *s, int n)
{
	char	*rv;
	char	*r;

	rv = (char *)malloc(n + 1);
	if (!rv)
		return (NULL);
	r = rv;
	while (r - rv < n)
		*r++ = *s++;
	*r = 0;
	return (rv);
}
