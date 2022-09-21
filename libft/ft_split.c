/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 20:01:20 by mcarolee          #+#    #+#             */
/*   Updated: 2021/04/22 23:47:06 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_alloc_for_split(const char *s, char c)
{
	int	wcnt;

	if (!s)
		return (NULL);
	wcnt = 0;
	while (*s++)
		wcnt += s[-1] != c && (*s == c || !*s);
	return ((char **)malloc((wcnt + 1) * sizeof(char *)));
}

static void	*free_split_err(char **r, int wcnt)
{
	while (wcnt)
		free(r[--wcnt]);
	free(r);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		wcnt;
	int		i;
	int		b;
	char	**r;

	r = ft_alloc_for_split(s, c);
	if (!r)
		return (NULL);
	wcnt = 0;
	i = -1;
	while (s[int_max(0, ++i - 1)])
		if ((!i || s[i - 1] == c) && s[i] != c)
			b = i;
	else if (i > 0 && s[i - 1] != c && (s[i] == c || !s[i]))
		r[wcnt++] = ft_substr(s, b, i - b);
	r[wcnt] = NULL;
	while (wcnt--)
		if (!r[wcnt])
			return (free_split_err(r, wcnt));
	return (r);
}

int	free_split(char **inf)
{
	int	i;

	i = 0;
	while (inf[i])
		free(inf[i++]);
	free(inf);
	return (0);
}
