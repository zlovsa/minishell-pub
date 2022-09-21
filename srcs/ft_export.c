#include "minishell.h"

void	print_expvar(t_list *min)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(min->cmd, 1);
	if (min->val)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(min->val, 1);
		ft_putchar_fd('"', 1);
	}
	ft_putchar_fd('\n', 1);
}

void	print_export(t_list *env)
{
	t_list	*t;
	t_list	*min;

	while (env)
	{
		min = env;
		t = min->prev;
		while (t)
		{
			if (ft_strcmp(t->cmd, min->cmd) < 0)
				min = t;
			t = t->prev;
		}
		if (ft_strcmp(min->cmd, "") && ft_strcmp(min->cmd, "_"))
			print_expvar(min);
		del_elem(min, &env);
	}
}

void	export(t_shell *sh, char *cmd)
{
	t_list	*v;
	char	*eqp;

	eqp = ft_strchr(cmd, '=');
	if (eqp)
		*eqp++ = 0;
	v = get_env(sh->env, cmd);
	if (v)
	{
		if (eqp)
		{
			free(v->val);
			v->val = ft_strdup(eqp);
		}
	}
	else
		add_list(ft_strdup(cmd), ft_strdup(eqp), &sh->env);
}

t_list	*ft_export(t_shell *sh, t_list *args)
{
	int	valid;

	sh->exitcode = 0;
	args = next_arg(args);
	if (!isarg(args))
		print_export(copy_list(sh->env));
	while (isarg(args))
	{
		valid = check_varname(args->cmd, '=');
		sh->exitcode |= !valid;
		if (!valid)
			ft_putendl_fd3("export: `", args->cmd,
				"': not a valid identifier", 2);
		else
			export(sh, args->cmd);
		args = next_arg(args);
	}
	return (next_sep(args));
}
