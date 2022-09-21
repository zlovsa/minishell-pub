#include "minishell.h"

t_list	*ft_env(t_shell *sh, t_list *args)
{
	t_list	*env;

	env = sh->env;
	while (env && env->prev)
		env = env->prev;
	while (env)
	{
		if (env->val)
		{
			ft_putstr_fd(env->cmd, 1);
			write(1, "=", 1);
			ft_putendl_fd(env->val, 1);
		}
		env = env->next;
	}
	sh->exitcode = 0;
	return (next_sep(args));
}

void	read_env(char **envp, t_list **env)
{
	char	*eqp;
	int		i;
	char	*val;
	char	*var;

	i = -1;
	*env = NULL;
	while (envp[++i])
	{
		eqp = ft_strchr(envp[i], '=');
		var = ft_strndup(envp[i], eqp - envp[i]);
		val = ft_strdup(eqp + 1);
		if (!ft_strcmp(var, "OLDPWD") || !ft_strcmp(var, "PWD"))
			continue ;
		if (!ft_strcmp(var, "SHLVL"))
		{
			eqp = ft_itoa(ft_atoi(val) + 1);
			free(val);
			val = eqp;
		}
		add_list(var, val, env);
	}
	if (!get_env(*env, "SHLVL"))
		add_list(ft_strdup("SHLVL"), ft_strdup("1"), env);
	update_pwd_vars(env, 0);
}

t_list	*get_env(t_list *env, char *var)
{
	while (env && ft_strcmp(env->cmd, var))
		env = env->prev;
	return (env);
}
