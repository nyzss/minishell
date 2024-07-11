/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_func_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:02:54 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/11 18:29:18 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	{
		printf("export ");
		if (!ft_strchr(*env_sort, '='))
			printf("%s\n", *env_sort++);
		else
		{
			write(STDOUT_FILENO, *env_sort,
				ft_strchr(*env_sort, '=') - *env_sort + 1);
			printf("\"%s\"\n", ft_strchr(*env_sort, '=') + 1);
		}
	}
	return (free(env_sort), 0);
}

int	bi_add_var(t_args *args, char ***env)
{
	char	**new_env;
	char	*new_var;
	int		i;

	if (!*(args->value) || *(args->value) == '=')
	{
		bi_err_export(args->value);
		return (0);
	}
	i = bi_get_var_export(args->value, *env);
	new_var = ft_strdup(args->value);
	if (!new_var)
		return (1);
	if (i >= 0)
	{
		free((*env)[i]);
		(*env)[i] = new_var;
		return (0);
	}
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

int	bi_get_var_export(char *var, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (bi_is_equal(var))
		{
			if (!ft_strncmp(var, env[i], ft_strchr(var, '=') - var)
				&& ft_strchr(env[i], '=') - env[i] == ft_strchr(var, '=') - var)
				return (i);
		}
		else
		{
			if (!ft_strcmp(var, env[i]))
				return (i);
		}
		i++;
	}
	return (-1);
}

int	bi_get_var_unset(char *var, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (bi_is_equal(env[i]))
		{
			if (!ft_strncmp(var, env[i], ft_strlen(var))
				&& ft_strchr(env[i], '=') - env[i] == ft_strlen(var))
				return (i);
		}
		else
		{
			if (!ft_strcmp(var, env[i]))
				return (i);
		}
		i++;
	}
	return (-1);
}

int	bi_del_var(t_args *args, char ***env)
{
	int		i;
	int		j;
	int		k;
	char	**new_env;

	i = bi_get_var_unset(args->value, *env);
	if (i < 0)
		return (0);
	new_env = (char **)malloc(ft_arr_size(*env) * sizeof(char *));
	if (!new_env)
		return (1);
	j = 0;
	k = 0;
	while ((*env)[j])
	{
		if (j == i)
			j++;
		new_env[k++] = (*env)[j++];
	}
	new_env[k] = NULL;
	free((*env)[i]);
	free(*env);
	*env = new_env;
}
