#include "minishell.h"

t_signal	g_signal;

int	char_arrow(char *str, t_shell *sh)
{
	if (ft_isprint(str[0]))
	{
		sh->chst->cmd = ft_strjoin_free(sh->chst->cmd, str);
		write(1, str, ft_strlen(str));
	}
	else if (!ft_strcmp(str, "\e[A") && sh->chst->prev)
	{
		del_cmd(ft_strlen(sh->chst->cmd));
		sh->chst = sh->chst->prev;
		ft_putstr_fd(sh->chst->cmd, 1);
	}
	else if (!ft_strcmp(str, "\e[B") && sh->chst->next)
	{
		del_cmd(ft_strlen(sh->chst->cmd));
		sh->chst = sh->chst->next;
		ft_putstr_fd(sh->chst->cmd, 1);
	}
	else if (!ft_strcmp(str, "\177") && *sh->chst->cmd)
	{
		sh->chst->cmd[ft_strlen(sh->chst->cmd) - 1] = 0;
		del_cmd(1);
	}
	else
		return (0);
	return (1);
}

void	handle_sig(t_shell *sh)
{
	if (g_signal.ctrlc)
	{
		free_list(sh->chst);
		sh->chst = copy_list(sh->hist);
		sh->exitcode = g_signal.exitcode;
		signal_init();
	}
	if (g_signal.sigq)
		signal_init();
}

void	read_cmd(t_shell *sh, char *str)
{
	int		l;

	l = read(0, str, 20000);
	str[l] = 0;
	handle_sig(sh);
	if (!char_arrow(str, sh) && !ft_strcmp(str, "\4") && !*sh->chst->cmd)
	{
		sh->chst->cmd = ft_strjoin_free(sh->chst->cmd, "exit");
		str[0] = '\n';
	}
}

int	main(int ac, char *av[], char const *envp[])
{
	t_shell	sh;
	char	str[20001];

	init_shell(&sh, ac, av, envp);
	while (1)
	{
		sh.chst = copy_list(sh.hist);
		signal_init();
		ft_putstr_fd("\e[32mminihell$\e[39m ", 2);
		str[0] = 0;
		while (ft_strcmp(str, "\n"))
			read_cmd(&sh, str);
		write(1, "\n", 1);
		exec(&sh);
		if (g_signal.ctrlc || g_signal.sigq)
			sh.exitcode = g_signal.exitcode;
	}
	free_shell(&sh);
}
