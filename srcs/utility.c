#include "minishell.h"

void	termcap_on(void)
{
	struct termios	term;
	static char		*term_name = "xterm-256color";

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, term_name);
}

void	termcap_off(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag |= ECHO;
	term.c_lflag |= ICANON;
	tcsetattr(0, TCSANOW, &term);
}

void	init_shell(t_shell *sh, int ac, char *av[], char const *envp[])
{
	sh->ac = ac;
	sh->av = av;
	sh->envp = (char **)envp;
	sh->hist = NULL;
	sh->exitcode = 0;
	sh->in_fd = -1;
	sh->out_fd = -1;
	read_env((char **)envp, &sh->env);
	termcap_on();
}

void	free_shell(t_shell *sh)
{
	free_list(sh->hist);
	free_list(sh->env);
	termcap_off();
}

void	del_cmd(int n)
{
	while (n--)
	{
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		tputs(tgetstr("le", 0), 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
	}
}
