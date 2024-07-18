/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:12:48 by okoca             #+#    #+#             */
/*   Updated: 2024/07/18 10:33:15 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ps_count_name(char *found)
{
	int	i;

	i = 0;
	if (ft_isdigit(found[i]) == 1 || found[i] == '?' || found[i] == '$')
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
	int		code;

	path = ps_getenv_name(found);
	if (path && ft_strcmp(path, "?") == 0)
	{
		free(path);
		if (g_signals.signal_code != 0)
		{
			code = g_signals.signal_code;
			g_signals.signal_code = 0;
			return (ft_itoa(code));
		}
		return (ft_itoa(ctx->exit_code));
	}
	else if (path && ft_strcmp(path, "$") == 0)
		return (free(path), ft_strdup("program_pid"));
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
