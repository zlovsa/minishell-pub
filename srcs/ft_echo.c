#include "minishell.h"

t_list	*ft_echo(t_shell *sh, t_list *argv)
{
	int	n_flag;

	n_flag = 0;
	argv = next_arg(argv);
	while (isarg(argv) && !ft_strcmp(argv->cmd, "-n"))
	{
		n_flag = 1;
		argv = next_arg(argv);
	}
	while (isarg(argv))
	{
		ft_putstr_fd(argv->cmd, 1);
		argv = next_arg(argv);
		if (isarg(argv))
			write(1, " ", 1);
	}
	if (!n_flag)
		write(1, "\n", 1);
	sh->exitcode = 0;
	return (next_sep(argv));
}
