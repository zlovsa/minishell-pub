#include "minishell.h"

void	run(t_shell *sh, t_list *args)
{
	char	**argv;
	char	**envp;

	argv = list_to_strarr(args, 0);
	envp = list_to_strarr(sh->env, 1);
	termcap_off();
	g_signal.pid = fork();
	if (g_signal.pid < 0)
	{
		ft_putendl_fd("fork error", 2);
		free_shell(sh);
		exit(sh->exitcode);
	}
	if (!g_signal.pid)
	{
		execve(argv[0], argv, envp);
		ft_putendl_fd("execve error", 2);
		free_shell(sh);
		exit(sh->exitcode);
	}
	waitpid(g_signal.pid, &sh->exitcode, 0);
	termcap_on();
	free_split(argv);
	free_split(envp);
}

t_list	*exec_bin(t_shell *sh, t_list *args)
{
	int		find;
	char	*full_path;

	find = find_exec(sh->env, args->cmd, &full_path);
	sh->exitcode = ((find == -1 || find == -4) * 127
			+ (find == -2 || find == -3) * 126) << 8;
	if (find == -1)
		ft_putendl_fd("No such file or directory", 2);
	else if (find == -2)
		ft_putendl_fd("Permission denied", 2);
	else if (find == -3)
		ft_putendl_fd("is a directory", 2);
	else if (find == -4)
		ft_putendl_fd("command not found", 2);
	else
	{
		free(args->cmd);
		args->cmd = full_path;
		run(sh, args);
	}
	return (next_sep(args));
}

t_list	*exec_to_sep(t_shell *sh, t_list *args)
{
	if (!set_in_out(sh, &args))
	{
		restore_in_out(sh);
		return (NULL);
	}
	if (args && !ft_strcmp("env", args->cmd))
		args = ft_env(sh, args);
	else if (args && !ft_strcmp("pwd", args->cmd))
		args = ft_pwd(sh, args);
	else if (args && !ft_strcmp("exit", args->cmd))
		args = ft_exit(sh, args);
	else if (args && !ft_strcmp("cd", args->cmd))
		args = ft_cd(sh, args);
	else if (args && !ft_strcmp("unset", args->cmd))
		args = ft_unset(sh, args);
	else if (args && !ft_strcmp("echo", args->cmd))
		args = ft_echo(sh, args);
	else if (args && !ft_strcmp("export", args->cmd))
		args = ft_export(sh, args);
	else if (!str_sep(args->cmd))
		args = exec_bin(sh, args);
	else
		args = next_sep(args);
	restore_in_out(sh);
	return (args);
}

void	exec_parsed(t_shell *sh, t_list **args)
{
	t_list	*t;

	t = *args;
	while (t)
	{
		sh->caller = 1;
		t = exec_to_sep(sh, t);
		t = reparse(sh->hist->cmd, sh, t, args);
		waitpid(-1, &sh->exitcode, 0);
		if (WIFEXITED(sh->exitcode))
			sh->exitcode = WEXITSTATUS(sh->exitcode);
		if (!sh->caller)
		{
			free_shell(sh);
			exit(sh->exitcode);
		}
	}
}

void	exec(t_shell *sh)
{
	t_list	*args;

	if (!parse_cmd(sh->chst->cmd, sh, &args))
	{
		ft_putendl_fd("syntax error", 2);
		sh->exitcode = 1;
		return ;
	}
	if (!args)
		return ;
	add_list(ft_strdup(sh->chst->cmd), NULL, &sh->hist);
	free_list(sh->chst);
	exec_parsed(sh, &args);
	free_list(args);
}
