/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:10:09 by okoca             #+#    #+#             */
/*   Updated: 2024/07/18 17:23:18 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ps_raw_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			break ;
		i++;
	}
	return (i);
}

t_token	*ps_get_quoted_str(char *str, char c, t_ctx *ctx)
{
	t_token			*new;
	int				len;
	t_token_type	type;

	len = 0;
	new = NULL;
	len = lex_quote_len(str, c) - 1;
	type = DOUBLEQUOTE;
	if (c == '\'')
		type = SINGLEQUOTE;
	if (len > 0)
		new = tok_create(str + 1, len, type, ctx);
	else
		new = tok_create("\0", 1, STRING, ctx);
	return (new);
}

t_token	*ps_parse_quotes(char *str, t_ctx *ctx)
{
	int		i;
	t_token	*token;
	t_token	*tmp;

	i = 0;
	token = NULL;
	tmp = NULL;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			tmp = ps_get_quoted_str(&(str[i]), str[i], ctx);
			i += ft_strlen(tmp->value) + 1;
		}
		else
		{
			tmp = tok_create(&(str[i]), ps_raw_len(&(str[i])), STRING, ctx);
			i += ft_strlen(tmp->value) - 1;
		}
		if (!tmp)
			return (NULL);
		tok_add_back(&(token), tmp);
		i++;
	}
	return (token);
}

char	*ps_combine_tokens(t_token *token)
{
	char	*value;

	value = NULL;
	while (token != NULL)
	{
		if (token->value != NULL)
		{
			value = ps_strjoin(value, token->value);
			if (value == NULL)
				break ;
		}
		token = token->next;
	}
	return (value);
}

int	ps_combine(t_token *token, t_token *new_list)
{
	t_token	*new_tmp;

	if (!new_list || !(new_list->value))
		return (0);
	new_tmp = new_list;
	new_list = new_list->next;
	if (token->value)
		free(token->value);
	token->value = new_tmp->value;
	free(new_tmp);
	if (!new_list)
		return (0);
	tok_last(new_list)->next = token->next;
	token->next = new_list;
	return (0);
}

// tok_debug(str);
// printf("----------\n");
int	ps_expand_and_quotes(t_token *token)
{
	t_token	*str;
	t_token	*new_list;
	t_token	*tmp;

	while (token != NULL)
	{
		tmp = token->next;
		if (token->type == STRING)
		{
			str = ps_parse_quotes(token->value, token->ctx);
			new_list = ps_expand_env(str);
			if (token->value)
				free(token->value);
			token->value = ps_combine_tokens(str);
			printf("token->value: %s\n", token->value);
			if (new_list)
				ps_combine(token, new_list);
			tok_free(str);
		}
		token = tmp;
	}
	return (0);
}
