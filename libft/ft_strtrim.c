/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:36:00 by mcarolee          #+#    #+#             */
/*   Updated: 2021/04/10 17:04:26 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_char_in_str(char c, const char *str)
{
	while (*str && *str != c)
		str++;
	return (*str == c);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	long	i;
	long	j;
	char	*r;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && ft_char_in_str(s1[i], set))
		i++;
	j = i;
	while (s1[j])
		j++;
	i--;
	j--;
	while (j > i && ft_char_in_str(s1[j], set))
		j--;
	r = (char *)malloc(j - i + 1);
	if (r)
	{
		ft_memcpy(r, s1 + i + 1, j - i);
		r[j - i] = 0;
	}
	return (r);
}
