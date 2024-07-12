/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:31:33 by okoca             #+#    #+#             */
/*   Updated: 2024/07/12 20:48:11 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ms_free_double(char **value)
{
	int	i;

	i = 0;
	while (value[i] != NULL)
	{
		free(value[i]);
		i++;
	}
	free(value);
	return (NULL);
}

/*
* pass in a env name for ex: `PATH` to get the `$PATH` or `HOME` for `$HOME`...
* returns a `char *` that doesn't need to be freed
*/
t_env	*ms_getenv(char *path, t_env *envp)
{
	if (envp == NULL || path == NULL)
		return (NULL);
	while (envp != NULL)
	{
		if (ft_strcmp(path, envp->id) == 0)
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}

char	*env_get_id(char *raw)
{
	char	*eq;

	if (!raw)
		return (NULL);
	eq = ft_strchr(raw, '=');
	if (!eq)
		return (ft_strdup(raw));
	else if (eq - raw == 0)
		return (NULL);
	return (ft_strndup(raw, eq - raw));
}

char	*env_get_value(char	*raw)
{
	char	*eq;

	if (!raw)
		return (NULL);
	eq = ft_strchr(raw, '=');
	if (!eq)
		return (NULL);
	else if (eq - raw == 0)
		return (NULL);
	return (ft_strdup(raw + (eq - raw + 1)));
}

int	env_lstsize(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

// ABC=hello_world
// ABCD=
// =abc
