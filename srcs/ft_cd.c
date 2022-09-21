#include "minishell.h"

void	update_pwd_vars(t_list **env, int cd)
{
	t_list	*pwd;
	t_list	*oldpwd;
	char	cwd[PATH_LEN];

	if (!getcwd(cwd, PATH_LEN))
		return ;
	if (!get_env(*env, "PWD"))
		add_list(ft_strdup("PWD"), NULL, env);
	pwd = get_env(*env, "PWD");
	if (cd)
	{
		if (!get_env(*env, "OLDPWD"))
			add_list(ft_strdup("OLDPWD"), NULL, env);
		oldpwd = get_env(*env, "OLDPWD");
		free(oldpwd->val);
		oldpwd->val = pwd->val;
	}
	pwd->val = ft_strdup(cwd);
}

t_list	*ft_cd(t_shell *sh, t_list *args)
{
	t_list	*home;
	t_list	*t;

	home = get_env(sh->env, "HOME");
	t = next_arg(args);
	if (isarg(t))
	{
		sh->exitcode = -chdir(t->cmd);
		if (sh->exitcode)
			ft_putendl_fd3("cd: ", t->cmd, ": No such file or directory", 2);
	}
	else
	{
		sh->exitcode = 1;
		if (home)
			sh->exitcode = -chdir(home->val);
		else
			ft_putendl_fd("cd: HOME not set", 2);
	}
	if (!sh->exitcode)
		update_pwd_vars(&sh->env, 1);
	return (next_sep(args));
}
