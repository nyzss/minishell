/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:33:35 by okoca             #+#    #+#             */
/*   Updated: 2024/07/11 16:23:54 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Check if the line is: `$ sdkjf`
*/
char	*ps_convert_to_env(char *str, char *found, char **envp)
{
	char	*tmp;
	char	*path;

	if (found - str == 0)
		tmp = ft_strdup("");
	else
		tmp = ft_strndup(str, found - str);
	if (!tmp)
		return (NULL);
	path = ps_getenv_name(found + 1);
	tmp = ps_strjoin(tmp, ms_getenv(path, envp));
	if (!tmp)
	{
		free(path);
		return (NULL);
	}
	tmp = ps_strjoin(tmp, found + (ft_strlen(path) + 1));
	if (path != NULL)
		free(path);
	if (ft_strlen(tmp) == 0)
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}

/*
* Try with a non-working only path for ex: `$sdofijsdf`
* could restructure this part to this:
* check if env var exists, if not just remove it from the string
* if it does exist: transform it with getenv
* ft_strjoin before the env var, put env, and strjoin after the env var
*/
int	ps_handle_env(t_token *token)
{
	char	*tmp;
	char	*found;

	while (token->value != NULL)
	{
		found = ft_strchr(token->value, '$');
		if (found == NULL)
			break ;
		if (ft_strlen(found) == 1)
			break ;
		tmp = token->value;
		token->value = ps_convert_to_env(token->value, found, token->ctx->env);
		free(tmp);
	}
	return (0);
}

/*
* token->value could be NULL!!
*/
int	ps_expand_env(t_token *token)
{
	while (token != NULL)
	{
		if (token->type == STRING || token->type == DOUBLEQUOTE)
			ps_handle_env(token);
		token = token->next;
	}
	return (0);
}
