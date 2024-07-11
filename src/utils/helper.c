/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:31:33 by okoca             #+#    #+#             */
/*   Updated: 2024/07/11 16:58:13 by okoca            ###   ########.fr       */
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

char	**ms_env_dup(char **envp)
{
	int		i;
	int		len;
	char	**new_env;

	i = 0;
	len = 0;
	while (envp[len] != NULL)
		len++;
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (NULL);
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
			return (ms_free_double(new_env));
		i++;
	}
	new_env[i] = ft_strdup("HELLO=HELLOWORLDTEST123456789");
	i++;
	new_env[i] = NULL;
	return (new_env);
}
