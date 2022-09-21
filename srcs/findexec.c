#include "minishell.h"

int	executable(char *dir, struct dirent *de, char **full_path)
{
	char		*f;
	struct stat	sb;
	int			st;
	int			r;

	if (de->d_type == DT_DIR)
		return (0);
	f = ft_strjoin(dir, "/");
	f = ft_strjoin_free(f, de->d_name);
	st = stat(f, &sb);
	r = !st && sb.st_mode & S_IXUSR;
	if (r)
		*full_path = f;
	else
		free(f);
	return (r);
}

int	find_in_dir(char *dirname, char *exec, char **full_path)
{
	DIR				*dir;
	struct dirent	*de;

	dir = opendir(dirname);
	de = readdir(dir);
	while (de)
	{
		if (!ft_strcmp(de->d_name, exec) && executable(dirname, de, full_path))
			break ;
		de = readdir(dir);
	}
	closedir(dir);
	if (de)
		return (1);
	return (0);
}

int	find_abs(char *exec, char **full_path)
{
	struct stat	sb;

	if (stat(exec, &sb) < 0)
		return (-1);
	if (sb.st_mode & S_IFDIR)
		return (-3);
	if (!(sb.st_mode & S_IXUSR))
		return (-2);
	*full_path = ft_strdup(exec);
	return (1);
}

int	find_exec(t_list *env, char *exec, char **full_path)
{
	t_list	*path;
	char	**dirs;
	int		i;

	if (ft_strchr(exec, '/'))
		return (find_abs(exec, full_path));
	else
	{
		path = get_env(env, "PATH");
		if (!path)
			return (-1);
		dirs = ft_split(path->val, ':');
		i = -1;
		while (dirs[++i])
			if (find_in_dir(dirs[i], exec, full_path))
				break ;
		free_split(dirs);
		if (!dirs[i])
			return (-4);
	}
	return (1);
}
