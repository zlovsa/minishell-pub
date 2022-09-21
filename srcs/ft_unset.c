#include "minishell.h"

int	check_varname(char *s, char nil)
{
	int	i;

	i = 0;
	while (s[i] == '_' || (i == 0 ? ft_isalpha(s[i]) : ft_isalnum(s[i])))
		i++;
	return (i > 0 && (!s[i] || s[i] == nil));
}

t_list	*ft_unset(t_shell *sh, t_list *args)
{
	int		valid;

	sh->exitcode = 0;
	args = next_arg(args);
	while (isarg(args))
	{
		valid = check_varname(args->cmd, 0);
		sh->exitcode |= !valid;
		if (!valid)
			ft_putendl_fd3("unset: `", args->cmd,
				"': not a valid identifier", 2);
		else
			del_elem(get_env(sh->env, args->cmd), &sh->env);
		args = next_arg(args);
	}
	return (next_sep(args));
}
