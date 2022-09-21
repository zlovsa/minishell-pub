/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:47:51 by mcarolee          #+#    #+#             */
/*   Updated: 2021/04/10 23:46:55 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	d;

	d = (unsigned char)*s1 - (unsigned char)*s2;
	while (!d && *s1++ && *s2++)
		d = (unsigned char)*s1 - (unsigned char)*s2;
	return (d);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		d;
	size_t	i;

	i = 0;
	d = (unsigned char)s1[i] - (unsigned char)s2[i];
	while (!d && s1[i] && s2[i] && i < n)
	{
		d = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (d)
			break ;
		i++;
	}
	return (d);
}

int	ft_str_starts_with(char *s, char *begin)
{
	while (*s == *begin && *s++ && *begin++)
		;
	return (!*begin);
}
