/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:54:57 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/10 13:09:57 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_do_exec(char *cmd, t_args *args, char **env)
{
	char	*path;
	char	**cmd;

	path = exe_get_path(cmd, env);
	if (!path)
		return (-1);
	cmd = exe_get_cmd(cmd, args);
	if (!cmd)
	{
		free(path);
		return (-1);
	}
	if (execve(path, cmd, env) == -1)
	{
		exe_err4_exec(path, errno);
		exe_free_all(cmd);
		free(path);
		return (-1);
	}
	exe_free_all(cmd);
	free(path);
	return (0);
}

char	*exe_get_path(char *file, char **env)
{
	char	**paths;
	char	*exec;

	if (!env || exe_is_abs_path(file) == 1)
		return (ft_strdup(file));
	paths = exe_get_allpaths(env);
	if (!paths)
		return (ft_strdup(file));
	exec = exe_get_exec(paths, file);
	exe_free_all(paths);
	return (exec);
}

char	*exe_get_exec(char **paths, char *file)
{
	char	*exec;
	char	*path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(path[i], "/");
		if (!path)
			return (NULL);
		exec = ft_strjoin(path, file);
		free(path);
		if (!exec)
			return (NULL);
		if (!access(exec, X_OK | F_OK))
			return (exec);
		free(exec);
	}
	return (NULL);
}

char	**exe_get_allpaths(char **env)
{
	int		i;
	char	*path_all;
	char	**paths;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			path_all = ft_strtrim(env[i], "PATH=");
			if (!path_all)
				return (NULL);
			paths = ft_split(path_all, ':');
			free(path_all);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	**exe_get_cmd(char *cmd, t_args *args)
{
	char	**cmds;
	int		arg_size;
	int		i;

	i = -1;
	arg_size = ft_lstsize(args);
	cmds = (char **)malloc((arg_size + 2) * sizeof(char *));
	if (!cmds)
		return (NULL);
	while (++i < arg_size + 1)
	{
		if (!i)
			cmds[i] = ft_strdup(cmd);
		else
			cmds[i] = ft_strdup(args->value);
		if (!cmds[i])
		{
			exe_free_all(cmds);
			return (NULL);
		}
	}
	cmds[i] = NULL;
	return (cmds);
}
