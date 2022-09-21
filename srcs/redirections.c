#include "minishell.h"

int	str_sep(char *str)
{
	return (!ft_strcmp("<", str) || !ft_strcmp(">", str)
		|| !ft_strcmp(">>", str) || !ft_strcmp("|", str)
		|| !ft_strcmp(";", str));
}

int	ft_input(t_shell *sh, t_list *key)
{
	close(sh->in_fd);
	if (!key || str_sep(key->cmd))
	{
		ft_putendl_fd("syntax error near unexpected token", 2);
		sh->exitcode = 258 << 8;
		return (258);
	}
	sh->in_fd = open(key->cmd, O_RDONLY, S_IRWXU);
	if (sh->in_fd < 0)
	{
		ft_putendl_fd("No such file or directory", 2);
		sh->exitcode = 1 << 8;
		return (1);
	}
	dup2(sh->in_fd, 0);
	return (0);
}

int	ft_pipe(t_shell *sh)
{
	int			pipe_fds[2];
	pid_t		pid;

	if (pipe(pipe_fds))
		return (!ft_putendl_fd("pipe error", 2));
	pid = fork();
	if (pid)
	{
		if (pipe_fds[0] > 0)
			close(pipe_fds[0]);
		dup2(pipe_fds[1], 1);
		sh->out_pipe = pipe_fds[1];
		return (1);
	}
	else
	{
		if (pipe_fds[1] > 0)
			close(pipe_fds[1]);
		dup2(pipe_fds[0], 0);
		sh->in_pipe = pipe_fds[0];
		sh->caller = 0;
		return (2);
	}
}

int	ft_output(t_shell *sh, t_list *key, char *type)
{
	close(sh->out_fd);
	if (!key || str_sep(key->cmd))
	{
		ft_putendl_fd("syntax error near unexpected token", 2);
		return (258);
	}
	if (!ft_strcmp(type, ">>"))
		sh->out_fd = open(key->cmd, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	else
		sh->out_fd = open(key->cmd, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (sh->out_fd < 0)
	{
		ft_putendl_fd("No such file or directory", 2);
		return (1);
	}
	dup2(sh->out_fd, 1);
	return (0);
}
