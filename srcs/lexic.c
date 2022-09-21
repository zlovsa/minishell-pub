#include "minishell.h"

int	cmd_sep(char c)
{
	return (c == '<' || c == '>' || c == ';' || c == '|');
}

t_list	*reparse(char *cmd, t_shell *sh, t_list *t, t_list **args)
{
	int		i;
	t_list	*ti;

	if (!t)
		return (t);
	i = 0;
	ti = *args;
	while (t != ti && ++i)
		ti = ti->next;
	free_list(*args);
	parse_cmd(cmd, sh, args);
	t = *args;
	while (i--)
		t = t->next;
	return (t);
}

int	lexic_check(t_list *args)
{
	while (args)
	{
		if (!ft_strcmp(args->cmd, ";") && !isarg(args->prev))
			return (0);
		if (!ft_strcmp(args->cmd, "|") && (!isarg(args->prev)
				|| !isarg(args->next)))
			return (0);
		if ((!ft_strcmp(args->cmd, ">") || !ft_strcmp(args->cmd, ">>")
				|| !ft_strcmp(args->cmd, "<")) && !isarg(args->next))
			return (0);
		args = args->next;
	}
	return (1);
}
