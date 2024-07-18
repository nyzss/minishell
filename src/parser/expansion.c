/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:33:35 by okoca             #+#    #+#             */
/*   Updated: 2024/07/18 10:32:41 by okoca            ###   ########.fr       */
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
	after_env = ps_get_after_env(found + 1);
	if (!after_env)
		return (free(before_env), free(env_var), NULL);
	new = ps_strjoin(before_env, env_var);
	if (!new)
		return (free(after_env), NULL);
	new = ps_strjoin(new, after_env);
	if (env_var)
		free(env_var);
	return (free(after_env), new);
}

/*
* Try with a non-working only path for ex: `$sdofijsdf`
* could restructure this part to this:
* check if env var exists, if not just remove it from the string
* if it does exist: transform it with getenv
* ft_strjoin before the env var, put env, and strjoin after the env var
*/
t_token	*ps_handle_env(t_token *token)
{
	char	*tmp;
	char	*found;

	if (token->value && ft_strcmp(token->value, "$") == 0)
		return (NULL);
	while (token->value != NULL)
	{
		found = ft_strchr(token->value, '$');
		if (found == NULL)
			break ;
		tmp = token->value;
		token->value = ps_convert_to_env(token->value, found, token->ctx);
		free(tmp);
	}
	return (ps_split_tokens(token, token->value));
}

int	ps_replace_current(t_token *current, t_token *new)
{
	t_token	*current_next;
	t_token	*new_tmp;
	char	*current_value;

	if (!current || !new)
		return (0);
	// temps
	current_value = current->value;
	current_next = current->next;


	//assignation
	tok_last(new)->next = current_next;
	current->value = new->value;
	current->next = new->next;

	new_tmp = new;
	new_tmp->value = NULL;
	new_tmp->next = NULL;


	// very end
	tok_free_one(new_tmp);
	free(current_value);
	return (0);
}

/*
* token->value could be NULL!!
*/
int	ps_expand_env(t_token *token)
{
	t_token	*new;

	while (token != NULL)
	{
		if (token->type == STRING || token->type == DOUBLEQUOTE)
		{
			new = ps_handle_env(token);
			// tok_debug(new);
			tok_free(new);
		}
		token = token->next;
	}
	return (0);
}

t_token	*ps_split_tokens(t_token *token, char *str)
{
	t_token	*tmp;
	t_token	*local;
	char	**words;
	int		i;

	i = 0;
	local = NULL;
	words = ft_split2(str, " \t\n");
	if (words == NULL)
		return (local);
	while (words[i])
	{
		tmp = tok_create(words[i], ft_strlen(words[i]), STRING, token->ctx);
		tok_add_back(&(local), tmp);
		free(words[i]);
		i++;
	}
	free(words);
	return (local);
}
// export TEST="ls -l -R -a"
