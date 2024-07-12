/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:54:57 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/12 20:50:04 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_do_exec(char *cmd, t_args *args, t_env *env)
{
	char	*path;
	char	**cmds;
	char	**envs;

	if (!cmd)
		return (0);
	path = exe_get_path(cmd, env);
	if (!path)
		return (-1);
	envs = exe_get_envs(env);
	if (!envs)
		return (free(path), -1);
	cmds = exe_get_cmds(cmd, args);
	if (!cmds)
		return (free(path), free(envs), -1);
	if (execve(path, cmds, envs) == -1)
	{
		exe_err4_exec(path, errno);
		ft_free_all(cmds);
		return (free(path), free(envs), -1);
	}
	ft_free_all(cmds);
	return (free(path), free(envs), 0);
}

char	*exe_get_path(char *file, t_env *env)
{
	char	**paths;
	char	*exec;

	if (!env || exe_is_abs_path(file) == 1)
		return (ft_strdup(file));
	paths = exe_get_allpaths(env);
	if (!paths)
		return (ft_strdup(file));
	exec = exe_get_exec(paths, file);
	ft_free_all(paths);
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
		path = ft_strjoin(paths[i], "/");
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

char	**exe_get_allpaths(t_env *env)
{
	char	**paths;
	t_env	*path_env;

	path_env = ms_getenv("PATH", env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env->value, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	**exe_get_cmds(char *cmd, t_args *args)
{
	char	**cmds;
	int		arg_size;
	int		i;

	i = -1;
	arg_size = arg_lstsize(args);
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
			ft_free_all(cmds);
			return (NULL);
		}
	}
	cmds[i] = NULL;
	return (cmds);
}
/* Only create a tab that holds the add of env->raw. No strdup on raw*/
char	**exe_get_envs(t_env *env)
{
	char	**envs;
	int		env_size;
	int		i;

	i = -1;
	env_size = env_lstsize(env);
	envs = (char **)malloc((env_size + 1) * sizeof(char *));
	if (!envs)
		return (NULL);
	while (++i < env_size)
	{
		envs[i] = env->raw;
		env = env->next;
	}
	envs[i] = NULL;
	return (envs);
}