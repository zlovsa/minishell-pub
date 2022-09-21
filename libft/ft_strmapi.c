/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 20:01:20 by mcarolee          #+#    #+#             */
/*   Updated: 2021/04/10 16:10:47 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	l;
	char	*r;

	if (!s || !f)
		return (NULL);
	l = ft_strlen(s);
	r = (char *)malloc(l + 1);
	if (!r)
		return (NULL);
	i = -1;
	while (++i < l)
		r[i] = (*f)(i, s[i]);
	r[i] = 0;
	return (r);
}
