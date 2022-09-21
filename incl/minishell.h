#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <term.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include "libft.h"

# define PATH_LEN 10000

typedef struct s_list
{
	char			*cmd;
	char			*val;
	int				type;
	struct s_list	*prev;
	struct s_list	*next;
}					t_list;

typedef struct s_shell
{
	t_list			*env;
	t_list			*hist;
	t_list			*chst;
	int				exitcode;
	int				ac;
	int				caller;
	int				in_pipe;
	int				in_fd;
	int				saved_in_fd;
	int				out_pipe;
	int				out_fd;
	int				saved_out_fd;
	char			**av;
	char			**envp;
}					t_shell;

typedef struct s_signal
{
	pid_t	pid;
	int		ctrlc;
	int		sigq;
	int		exitcode;
}	t_signal;

t_list				*ft_pwd(t_shell *sh, t_list *args);
t_list				*ft_echo(t_shell *sh, t_list *argv);
t_list				*ft_env(t_shell *sh, t_list *args);
t_list				*ft_exit(t_shell *sh, t_list *args);
t_list				*ft_cd(t_shell *sh, t_list *args);
t_list				*ft_unset(t_shell *sh, t_list *args);
t_list				*ft_export(t_shell *sh, t_list *args);
void				init_shell(t_shell *sh, int ac, char *av[],
						char const *envp[]);
void				read_env(char **envp, t_list **env);
int					check_varname(char *s, char nil);
t_list				*get_env(t_list *env, char *var);
t_list				*add_list(char *cmd, char *val, t_list **list);
t_list				*copy_list(t_list *list);
void				free_list(t_list *list);
void				del_elem(t_list *elem, t_list **list);
int					parse_cmd(char *cmd, t_shell *sh, t_list **args);
t_list				*reparse(char *cmd, t_shell *sh, t_list *t, t_list **args);
int					lexic_check(t_list *args);
int					find_exec(t_list *env, char *exec, char **full_path);
int					len_list(t_list *list);
int					args_count(t_list *list);
t_list				*next_arg(t_list *arg);
char				**list_to_strarr(t_list *lst, int env);
t_list				*next_sep(t_list *args);
int					isarg(t_list *arg);
int					str_sep(char *str);
int					cmd_sep(char c);
void				free_shell(t_shell *sh);
int					ft_pipe(t_shell *sh);
int					ft_input(t_shell *sh, t_list *key);
int					ft_output(t_shell *sh, t_list *key, char *type);
int					set_in_out(t_shell *sh, t_list **args);
void				restore_in_out(t_shell *sh);
void				exec(t_shell *sh);
void				termcap_off(void);
void				termcap_on(void);
void				del_cmd(int n);
void				update_pwd_vars(t_list **env, int cd);
void				signal_init(void);
void				signal_int(int nbr);
void				signal_quit(int nbr);

extern t_signal	g_signal;

#endif
