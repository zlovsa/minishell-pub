/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 17:43:44 by phelen            #+#    #+#             */
/*   Updated: 2021/04/19 02:13:39 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_init(void)
{
	g_signal.pid = 0;
	g_signal.ctrlc = 0;
	g_signal.sigq = 0;
	g_signal.exitcode = 0;
	signal(SIGINT, &signal_int);
	signal(SIGQUIT, &signal_quit);
}

void	signal_int(int nbr)
{
	(void)nbr;
	if (g_signal.pid)
	{
		ft_putstr_fd("\n", 2);
		g_signal.exitcode = 130;
	}
	else
	{
		ft_putstr_fd("\n\e[32mminihell$\e[39m ", 2);
		g_signal.exitcode = 1;
	}
	g_signal.ctrlc = 1;
}

void	signal_quit(int nbr)
{
	(void)nbr;
	if (g_signal.pid)
	{
		ft_putendl_fd("Quit: 3", 2);
		g_signal.exitcode = 131;
		g_signal.sigq = 1;
	}
}
