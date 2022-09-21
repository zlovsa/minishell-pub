/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:36:00 by mcarolee          #+#    #+#             */
/*   Updated: 2021/04/10 16:08:14 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	char	*t;

	r = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!r)
		return (NULL);
	t = r;
	while (s1 && *s1)
		*t++ = *s1++;
	while (s2 && *s2)
		*t++ = *s2++;
	*t = 0;
	return (r);
}

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*t;

	t = ft_strjoin(s1, s2);
	free(s1);
	return (t);
}

char	*ft_strjoin_char(char *s1, char c)
{
	char	s2[2];

	s2[0] = c;
	s2[1] = 0;
	return (ft_strjoin_free(s1, s2));
}
