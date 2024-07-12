/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:33:35 by okoca             #+#    #+#             */
/*   Updated: 2024/07/13 00:05:46 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* echo "$12345" -> be careful of this
* echo "$<abcdef" -> too
* echo "$/?lol" -> too
*/
char	*ps_convert_to_env(char *str, char *found, t_ctx *ctx)
{
	char	*before_env;
	char	*env_var;
	char	*after_env;
	char	*new;

	before_env = ps_get_before_env(str, found);
	if (!before_env)
		return (NULL);
	env_var = ps_get_env_var(found + 1, ctx);
	if (!env_var)
		return (free(before_env), NULL);
	after_env = ps_get_after_env(found + 1);
	if (!after_env)
		return (free(before_env), NULL);
	new = ps_strjoin(before_env, env_var);
	if (!new)
		return (free(before_env), free(after_env), NULL);
	new = ps_strjoin(new, after_env);
	if (!new)
		return (free(before_env), free(after_env), NULL);
	return (free(after_env), new);
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
		token->value = ps_convert_to_env(token->value, found, token->ctx);
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
