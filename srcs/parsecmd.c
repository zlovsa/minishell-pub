#include "minishell.h"

char	*read_envvar(char *cmd, t_shell *sh, t_list *t)
{
	char	*b;
	t_list	*v;

	b = ++cmd;
	while (*cmd && ((b == cmd && ft_isalpha(*cmd))
			|| (b != cmd && ft_isalnum(*cmd)) || *cmd == '_'))
		cmd++;
	if (b == cmd && *cmd != '?')
		t->cmd = ft_strjoin_char(t->cmd, '$');
	else if (b == cmd && *cmd == '?')
	{
		b = ft_itoa(sh->exitcode);
		t->cmd = ft_strjoin_free(t->cmd, b);
		free(b);
		cmd++;
	}
	else
	{
		b = ft_strndup(b, cmd - b);
		v = get_env(sh->env, b);
		free(b);
		if (v)
			t->cmd = ft_strjoin_free(t->cmd, v->val);
	}
	return (--cmd);
}

char	*read_bslash(char *cmd, t_list *t, int dblq)
{
	if (!cmd[1])
		return (NULL);
	if (!dblq || cmd[1] == '$' || cmd[1] == '"' || cmd[1] == '\\')
		cmd++;
	t->cmd = ft_strjoin_char(t->cmd, *cmd);
	return (cmd);
}

char	*read_quotes(char *cmd, t_shell *sh, t_list *t)
{
	char	q;

	q = *cmd;
	cmd++;
	while (cmd && *cmd && *cmd != q)
	{
		if (q == '"' && *cmd == '$')
			cmd = read_envvar(cmd, sh, t);
		else if (q == '"' && *cmd == '\\')
			cmd = read_bslash(cmd, t, 1);
		else
			t->cmd = ft_strjoin_char(t->cmd, *cmd);
		cmd++;
	}
	if (cmd && *cmd == q)
		return (cmd);
	return (NULL);
}

char	*read_argument(char *cmd, t_shell *sh, t_list **args, t_list **t)
{
	if (!*t)
		*t = add_list(ft_strdup(""), NULL, args);
	if (*cmd == '"' || *cmd == '\'')
		cmd = read_quotes(cmd, sh, *t);
	else if (*cmd == '$')
		cmd = read_envvar(cmd, sh, *t);
	else if (*cmd == '\\')
		cmd = read_bslash(cmd, *t, 0);
	else
		(*t)->cmd = ft_strjoin_char((*t)->cmd, *cmd);
	return (cmd);
}

int	parse_cmd(char *cmd, t_shell *sh, t_list **args)
{
	t_list	*t;

	*args = NULL;
	t = NULL;
	while (cmd && *cmd)
	{
		if (*cmd != ' ' && !cmd_sep(*cmd))
			cmd = read_argument(cmd, sh, args, &t);
		else
		{
			if (cmd_sep(*cmd))
				add_list(ft_strndup(cmd, 1 + (cmd[1] == '>')), NULL, args);
			if (cmd[0] == '>' && cmd[1] == '>')
				cmd++;
			t = NULL;
		}
		if (cmd)
			cmd++;
	}
	while (*args && (*args)->prev)
		*args = (*args)->prev;
	return (!!cmd && lexic_check(*args));
}
