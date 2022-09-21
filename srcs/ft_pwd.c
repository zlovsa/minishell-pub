#include "minishell.h"

t_list	*ft_pwd(t_shell *sh, t_list *args)
{
	char	cwd[PATH_LEN];

	sh->exitcode = 1;
	if ((getcwd(cwd, PATH_LEN)))
	{
		ft_putendl_fd(cwd, 1);
		sh->exitcode = 0;
	}
	return (next_sep(args));
}
