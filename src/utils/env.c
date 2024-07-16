/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:20:28 by okoca             #+#    #+#             */
/*   Updated: 2024/07/16 10:48:56 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ms_env_dup(char **envp)
{
	int		i;
	char	*id;
	char	*value;
	t_env	*new_env;
	t_env	*tmp;

	i = 0;
	new_env = NULL;
	if (!envp || (envp && *envp == NULL))
		return (env_default_env());
	while (envp[i])
	{
		id = env_get_id(envp[i]);
		value = env_get_value(envp[i]);
		tmp = env_create(id, value, ft_strdup(envp[i]));
		if (!tmp)
			return (NULL);
		env_add_back(&new_env, tmp);
		i++;
	}
	return (new_env);
}

t_env	*env_create(char *id, char *value, char *raw)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		free(id);
		free(value);
		return (NULL);
	}
	new->id = id;
	new->value = value;
	new->raw = raw;
	new->next = NULL;
	return (new);
}

int	env_add_back(t_env **head, t_env *new)
{
	t_env	*tmp;

	if (*head == NULL)
		*head = new;
	else
	{
		tmp = (*head);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

void	env_del_one(t_env *env)
{
	if (env->id)
		free(env->id);
	if (env->value)
		free(env->value);
	if (env->raw)
		free(env->raw);
	free(env);
}

void	env_free(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		env_del_one(tmp);
	}
}
