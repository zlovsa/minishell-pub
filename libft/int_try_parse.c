/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_try_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 01:13:03 by mcarolee          #+#    #+#             */
/*   Updated: 2021/04/10 17:23:22 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	int_try_parse(char *str, int *out)
{
	long	sign;
	long	rv;

	if (!str)
		return (0);
	rv = 0;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while ('0' <= *str && *str <= '9')
		rv = rv * 10 + sign * (*str++ - '0');
	if (*str || rv != (int)rv)
		return (0);
	*out = rv;
	return (1);
}

int	long_try_parse(char *str, long *out)
{
	long long	sign;
	long long	rv;

	if (!str)
		return (0);
	rv = 0;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while ('0' <= *str && *str <= '9')
		rv = rv * 10 + sign * (*str++ - '0');
	if (*str || rv != (long)rv)
		return (0);
	*out = rv;
	return (1);
}

int	int_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	int_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
