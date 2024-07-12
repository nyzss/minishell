/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:12:48 by okoca             #+#    #+#             */
/*   Updated: 2024/07/13 00:15:18 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ps_count_name(char *found)
{
	int	i;

	i = 0;
	if (ft_isdigit(found[i]) == 1 || found[i] == '?')
		return (1);
	while (found[i])
	{
		if (found[i] != '_' && ft_isalnum(found[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

char	*ps_getenv_name(char *found)
{
	int		len;
	char	*name;

	len = ps_count_name(found);
	name = ft_strndup(found, len);
	return (name);
}

// $hello
// wow$path
char	*ps_get_before_env(char *str, char *found)
{
	int		len;

	len = found - str;
	if (len == 0)
		return (ft_strdup(""));
	return (ft_strndup(str, len));
}

char	*ps_get_env_var(char *found, t_ctx *ctx)
{
	char	*path;
	t_env	*env_var;

	path = ps_getenv_name(found);
	if (path && ft_strcmp(path, "?") == 0)
		return (free(path), ft_itoa(ctx->exit_code));
	env_var = ms_getenv(path, ctx->envp);
	if (path)
		free(path);
	if (!env_var)
		return (NULL);
	return (ft_strdup(env_var->value));
}

char	*ps_get_after_env(char *found)
{
	int		len;
	char	*new;

	len = ps_count_name(found);
	new = ft_strdup(found + len);
	return (new);
}
