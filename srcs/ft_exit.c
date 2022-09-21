#include "minishell.h"

int	piped(t_list *args)
{
	while (args && args->prev && ft_strcmp(args->prev->cmd, ";"))
		args = args->prev;
	while (args && ft_strcmp(args->cmd, "|") && ft_strcmp(args->cmd, ";"))
		args = args->next;
	if (!args)
		return (0);
	return (!ft_strcmp(args->cmd, "|"));
}

t_list	*ft_exit(t_shell *sh, t_list *args)
{
	if (args_count(args) > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		sh->exitcode = 1;
		return (next_sep(args));
	}
	sh->exitcode = 0;
	if (sh->caller && !piped(args))
		ft_putendl_fd("exit", 2);
	if (args_count(args) == 2)
	{
		sh->exitcode = 255;
		args = next_arg(args);
		if (!int_try_parse(args->cmd, &sh->exitcode))
			ft_putendl_fd3("exit: ", args->cmd,
				": numeric argument required", 2);
	}
	if (!sh->caller || !piped(args))
	{
		free_shell(sh);
		free_list(args);
		exit(sh->exitcode);
	}
	return (NULL);
}
