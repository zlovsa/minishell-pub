/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 00:20:33 by mcarolee          #+#    #+#             */
/*   Updated: 2021/04/10 17:19:12 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_listgnl	*get_list(t_listgnl **all, int fd)
{
	t_listgnl	*t;

	t = *all;
	while (t && t->fd != fd)
		t = t->next;
	if (t)
		return (t);
	t = (t_listgnl *)malloc(sizeof(t_listgnl));
	if (!t)
		return (NULL);
	t->next = *all;
	t->fd = fd;
	t->tail = ft_strdup("");
	if (!t->tail)
	{
		free(t);
		return (NULL);
	}
	*all = t;
	return (t);
}

int	read_to_lf(char **str, int fd)
{
	char	*buf;
	long	rcnt;
	char	*tmp;

	if (ft_strchr(*str, '\n'))
		return (1);
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	if (!ft_strchr(*str, '\n'))
		rcnt = read(fd, buf, BUFFER_SIZE);
	while (!ft_strchr(*str, '\n') && rcnt > 0)
	{
		buf[rcnt] = 0;
		tmp = *str;
		*str = ft_strjoin(*str, buf);
		if (!*str)
		{
			free(buf);
			return (-1);
		}
		free(tmp);
	}
	free(buf);
	return (rcnt);
}

int	split(char **line, char **tail)
{
	long	l;
	long	i;
	char	*t;

	l = 0;
	while ((*tail)[l] && (*tail)[l] != '\n')
		l++;
	*line = (char *)malloc(l + 1);
	if (!*line)
		return (-1);
	i = -1;
	while (++i < l)
		(*line)[i] = (*tail)[i];
	(*line)[l] = 0;
	if ((*tail)[l])
		t = ft_strdup(*tail + l + 1);
	else
		t = ft_strdup("");
	if (!t)
		return (-1);
	free(*tail);
	*tail = t;
	return (1);
}

void	del_fd(t_listgnl **all, t_listgnl *del)
{
	t_listgnl	*t;
	t_listgnl	*p;

	p = NULL;
	t = *all;
	while (t != del)
	{
		p = t;
		t = t->next;
	}
	if (p)
		p->next = t->next;
	else
		*all = t->next;
	free(t);
}

int	get_next_line(int fd, char **line)
{
	static t_listgnl	*all;
	t_listgnl			*cur;
	int					rcnt;

	if (BUFFER_SIZE < 1 || fd < 0 || !line)
		return (-1);
	cur = get_list(&all, fd);
	if (!cur)
		return (-1);
	rcnt = read_to_lf(&(cur->tail), fd);
	if (rcnt < 0)
	{
		*line = NULL;
		free(cur->tail);
		del_fd(&all, cur);
		return (-1);
	}
	if (!rcnt)
	{
		*line = cur->tail;
		del_fd(&all, cur);
		return (0);
	}
	return (split(line, &(cur->tail)));
}
