/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:31:33 by okoca             #+#    #+#             */
/*   Updated: 2024/07/12 11:05:06 by okoca            ###   ########.fr       */
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
char	*ms_getenv(char *path, char **envp)
{
	int	i;
	int	path_len;

	i = 0;
	if (envp == NULL || path == NULL)
		return (NULL);
	path_len = ft_strlen(path);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], path, path_len) == 0
			&& envp[i][path_len] == '=')
			return (&(envp[i][path_len + 1]));
		i++;
	}
	return (NULL);
}

t_env	*ms_env_dup(char **envp)
{
	int		i;
	int		j;
	char	*id;
	char	*value;
	t_env	*new_env;
	t_env	*tmp;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		id = ft_strndup(envp[i], j);
		if (j < ft_strlen(envp[i]))
			value = ft_strdup(envp[i] + j);
		else
			value = NULL;
		tmp = env_create(id, value);
		if (!tmp)
			retur (NULL);
		env_add_back(&new_env, tmp);
		i++;
	}
	return (new_env);
}
