/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:34:33 by okoca             #+#    #+#             */
/*   Updated: 2024/07/11 12:04:16 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	else
		return (0);
}

int	bi_do_builtin(char *cmd, t_args *args, char ***env)
{
	if (!ft_strcmp(cmd, "echo"))
		return (bi_echo(args));
	else if (!ft_strcmp(cmd, "cd"))
		return (bi_cd(args));
	else if (!ft_strcmp(cmd, "pwd"))
		return (bi_pwd(args));
	else if (!ft_strcmp(cmd, "export"))
		return (bi_export(args, env));
	else if (!ft_strcmp(cmd, "unset"))
		return (bi_unset(args, env));
	else if (!ft_strcmp(cmd, "env"))
		return (bi_env(args, *env));
	else if (!ft_strcmp(cmd, "exit"))
		return (bi_exit(args));
	else
		return (0);
}

char	**bi_get_new_vars(int cnt, t_args *args)
{
	char	**new_vars;
	int		i;

	i = 0;
	new_vars = (char **)malloc((cnt + 1) * sizeof(char *));
	if (!new_vars)
		return (NULL);
	while (i < cnt)
	{
		new_vars[i] = ft_strdup(args->value);
		if (!new_vars[i++])
		{
			ft_free_all(new_vars);
			return (NULL);
		}
		args = args->next;
	}
	new_vars[i] = NULL;
	return (new_vars);
}

int	bi_export(t_args *args, char ***env)
{
	int		cnt;
	int		size_env;
	char	**new_env;
	char	**new_vars;
	int		i;
	int		j;

	i = -1;
	j = 0;
	cnt = ft_lstsize(args);
	if (!cnt)
		if (bi_print_export(*env))
			return (1);
	else
	{
		new_vars = bi_get_new_vars(cnt, args);
		if (!new_vars)
			return (1);
		size_env = ft_arr_size(*env);
		new_env = (char **)malloc((size_env + cnt + 1) * sizeof(char *));
		if (!new_env)
		{
			ft_free_all(new_vars);
			return (1);
		}
		while (++i < size_env)
			new_env[i] = (*env)[i];
		while (j < cnt)
			new_env[i++] = new_vars[j++];
		new_env[i] = NULL;
		free(*env);
		*env = new_env;
	}
	return (0);
}

int	bi_print_export(char **env)
{
	int		size;
	int		i;
	char	**env_sort;

	size = ft_arr_size(env);
	i = -1;
	env_sort = (char **)malloc((size + 1) * sizeof(char *));
	if (!env_sort)
		return (1);
	while (++i < size + 1)
		env_sort[i] = env[i];
	ft_advanced_sort_string_tab(env_sort, &ft_strcmp);
	while (*env_sort)
		printf("export %s\n", *env_sort++);
	free(env_sort);
	return (0);
}

int	bi_unset(t_args *args, char ***env)
{
	return (0);
}