/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_func_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:02:54 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/12 16:06:11 by okoca            ###   ########.fr       */
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

t_env	*bi_new_var(char *arg_id, char *arg_value, t_args *args, t_env **env)
{
	t_env	*tmp;
	char	*arg_raw;

	arg_raw = ft_strdup(args->value);
	if (!arg_raw)
		return (NULL);
	tmp = ms_getenv(arg_id, *env);
	if (tmp)
	{
		if (tmp->value)
			free(tmp->value);
		tmp->value = arg_value;
		tmp->raw = arg_raw;
		return (free(arg_id), tmp);
	}
	tmp = env_create(arg_id, arg_value, arg_raw);
	if (!tmp)
	{
		if (arg_value)
			free(arg_value);
		return (free(arg_id), free(arg_raw), NULL);
	}
	return (tmp);
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
	if (bi_new_var(arg_id, arg_value, args, env) == NULL)
		return (1);
	env_add_back(env, tmp);
	return (0);
}

t_env	*bi_get_var(char *var, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(var, env->id))
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	bi_del_var(t_args *args, t_env **env)
{
	char	*arg_id;
	t_env	*tmp;
	t_env	*tmp2;

	arg_id = env_get_id(args->value);
	if (!arg_id)
		return (0);
	tmp = bi_get_var(arg_id, *env);
	if (!tmp)
		return (free(arg_id), 0);
	free(arg_id);
	if (*env == tmp)
		*env = tmp->next;
	tmp2 = *env;
	while (tmp2->next)
	{
		if (tmp2->next == tmp)
			tmp2->next = tmp->next;
		tmp2 = tmp2->next;
	}
	env_free(tmp);
	return (0);
}
