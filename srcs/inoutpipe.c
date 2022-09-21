#include "minishell.h"

int	isargredir(t_list *t)
{
	return (t && ft_strcmp(t->cmd, ";"));
}

int	set_pipe(t_shell *sh, t_list *t, t_list **args)
{
	int	pipe;

	pipe = ft_pipe(sh);
	if (!pipe)
		return (0);
	if (pipe == 2)
	{
		*args = t->next;
		set_in_out(sh, args);
	}
	return (1);
}

int	set_in_out(t_shell *sh, t_list **args)
{
	t_list	*t;

	sh->saved_out_fd = dup(1);
	sh->out_fd = 1;
	sh->saved_in_fd = dup(0);
	sh->in_fd = 0;
	t = *args;
	while (isargredir(t))
	{
		if (!ft_strcmp(t->cmd, "<") && ft_input(sh, t->next))
			return (0);
		else if ((!ft_strcmp(t->cmd, ">") || !ft_strcmp(t->cmd, ">>"))
			&& ft_output(sh, t->next, t->cmd))
			return (0);
		else if (!ft_strcmp(t->cmd, "|"))
			return (set_pipe(sh, t, args));
		if (!ft_strcmp(t->cmd, ">") || !ft_strcmp(t->cmd, ">>")
			|| !ft_strcmp(t->cmd, "<"))
			t = t->next;
		t = t->next;
	}
	return (1);
}

void	restore_in_out(t_shell *sh)
{
	close(sh->out_fd);
	dup2(sh->saved_out_fd, 1);
	close(sh->in_fd);
	dup2(sh->saved_in_fd, 0);
	if (sh->in_pipe > 0)
		close(sh->in_pipe);
	if (sh->out_pipe > 0)
		close(sh->out_pipe);
}
