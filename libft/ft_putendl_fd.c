/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:40:11 by mcarolee          #+#    #+#             */
/*   Updated: 2021/04/23 02:16:43 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	return (ft_putstr_fd(s, fd) + write(fd, "\n", 1));
}

int	ft_putendl_fd2(char *s1, char *s2, int fd)
{
	return (ft_putstr_fd(s1, fd) + ft_putstr_fd(s2, fd) + write(fd, "\n", 1));
}

int	ft_putendl_fd3(char *s1, char *s2, char *s3, int fd)
{
	return (ft_putstr_fd(s1, fd) + ft_putstr_fd(s2, fd) + ft_putstr_fd(s3, fd)
		+ write(fd, "\n", 1));
}
