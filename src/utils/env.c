/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:20:28 by okoca             #+#    #+#             */
/*   Updated: 2024/07/12 10:28:15 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_create(char *id, char *value)
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
	new->next = NULL;
	return (new);
}

t_env	*env_last(t_env *env)
{
	while (env->next != NULL)
		env = env->next;
	return (env);
}

int	env_add_back(t_env **head, t_env *new)
{
	if (new == NULL)
		return (1);
	if (*head == NULL)
		*head = new;
	else
		env_last(*head)->next = new;
	return (0);
}

void	env_free(t_env *env)
{
	t_env	*tmp;

	while (env != NULL)
	{
		tmp = env;
		if (env->id)
			free(env->id);
		if (env->value)
			free(env->value);
		env = env->next;
		free(tmp);
	}
}