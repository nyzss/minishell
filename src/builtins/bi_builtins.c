/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:34:33 by okoca             #+#    #+#             */
/*   Updated: 2024/07/11 14:47:14 by tsuchen          ###   ########.fr       */
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

int	bi_add_var(t_args *args, char ***env)
{
	char	**new_env;
	char	*new_var;
	int		i;

	i = -1;
	if (!*(args->value)	|| *(args->value) == '=')
	{
		bi_err_export(args->value);
		return (1);
	}
	new_var = ft_strdup(args->value);
	if (!new_var)
		return (1);
	new_env = (char **)malloc((ft_arr_size(*env) + 2) * sizeof(char *));
	if (!new_env)
		return (free(new_var), 1);
	while ((*env)[++i])
		new_env[i] = (*env)[i];
	new_env[i++] = new_var;
	new_env[i] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}

int	bi_export(t_args *args, char ***env)
{
	if (!args)
	{
		if (bi_print_export(*env))
			return (1);
	}
	else
	{
		while (args)
		{
			if (bi_add_var(args, env))
				return (1);
			args = args->next;
		}		
	}
	return (0);
}

int	bi_unset(t_args *args, char ***env)
{
	return (0);
}