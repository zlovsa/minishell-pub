/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:40:11 by mcarolee          #+#    #+#             */
/*   Updated: 2021/04/10 13:52:50 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_rec(long n, int fd)
{
	char	c;

	c = '0' + n % 10;
	if (n)
		return (nbr_rec(n / 10, fd) + write(fd, &c, 1));
	return (0);
}

int	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (n < 0)
		nb *= -1;
	return (write(fd, "-", n < 0) + write(fd, "0", n == 0) + nbr_rec(nb, fd));
}
