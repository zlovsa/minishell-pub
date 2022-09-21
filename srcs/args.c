#include "minishell.h"

char	**list_to_strarr(t_list *lst, int env)
{
	char	**r;
	char	*n;

	n = ft_strdup("");
	while (env && lst && lst->prev)
		lst = lst->prev;
	while (isarg(lst) && ft_strcmp(lst->cmd, "|"))
		if (str_sep(lst->cmd))
			lst = lst->next->next;
	else
	{
		n = ft_strjoin_free(n, lst->cmd);
		if (env)
		{
			n = ft_strjoin_free(n, "=");
			n = ft_strjoin_free(n, lst->val);
		}
		n = ft_strjoin_free(n, "\n");
		lst = lst->next;
	}
	r = ft_split(n, '\n');
	free(n);
	return (r);
}

int	isarg(t_list *arg)
{
	return (arg && ft_strcmp(arg->cmd, ";") && ft_strcmp(arg->cmd, "|"));
}

t_list	*next_arg(t_list *arg)
{
	arg = arg->next;
	while (arg && (!ft_strcmp("<", arg->cmd) || !ft_strcmp(">", arg->cmd)
			|| !ft_strcmp(">>", arg->cmd) || !ft_strcmp("|", arg->cmd)
			|| !ft_strcmp(";", arg->cmd)))
		if (!ft_strcmp("<", arg->cmd) || !ft_strcmp(">", arg->cmd)
			|| !ft_strcmp(">>", arg->cmd))
			arg = arg->next->next;
	else if (str_sep(arg->cmd))
		return (arg);
	else
		arg = arg->next;
	return (arg);
}

t_list	*next_sep(t_list *args)
{
	while (args && ft_strcmp(args->cmd, ";"))
		args = args->next;
	if (args)
		return (args->next);
	return (args);
}

int	args_count(t_list *list)
{
	int	l;

	l = 0;
	while (isarg(list))
	{
		if (str_sep(list->cmd))
		{
			l--;
			list = list->next;
		}
		l++;
		list = list->next;
	}
	return (l);
}
