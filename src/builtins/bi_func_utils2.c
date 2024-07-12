/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_func_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:02:54 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/12 14:03:07 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_print_export(t_env *env)
{
	t_env	*env_sort;

	env_sort = bi_dup_list(env); // create duplicate list function
	ft_list_sort(&env_sort, &ft_strcmp); //added list sort function
	while (env_sort)
	{
		printf("export %s", env_sort->id);
		if (env_sort->value)
			printf("=\"%s\"", env_sort->value);
		printf("\n");
		env_sort = env_sort->next;
	}
	ft_lstclear(env_sort, &free); // create lstclear and free function
	return (0);
}

int	bi_add_var(t_args *args, t_env **env)
{
	char	*arg_id;
	char	*arg_value;
	t_env	*tmp;

	arg_id = env_get_id(args->value);
	if (!arg_id)
		return (bi_err_export(args->value));
	arg_value = env_get_value(args->value);
	tmp = bi_get_var_export(args->value, *env);
	if (tmp)
	{
		if (tmp->value)
			free(tmp->value);
		tmp->value = arg_value;
		return (free(arg_id), 0);
	}
	tmp = env_create(arg_id, arg_value);
	if (!tmp)
	{
		if (arg_value)
			free(arg_value);
		return (free(arg_id), 1);
	}
	env_add_back(env, tmp);
	return (0);
}

int	bi_add_var(t_args *args, char ***env)
{
	char	**new_env;
	char	*new_var;
	int		i;

	if (!*(args->value) || *(args->value) == '=')
		return (bi_err_export(args->value));
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

t_env	*bi_get_var_export(char *var, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(var, env->id))
			return (env);
		env = env->next;
	}
	return (NULL);
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
				&& ft_strchr(env[i], '=') - env[i] == (long)ft_strlen(var))
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
	return (0);
}
