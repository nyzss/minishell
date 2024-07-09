/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:10:09 by okoca             #+#    #+#             */
/*   Updated: 2024/07/09 17:46:41 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ps_get_raw_len(char *str)
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

t_token	*ps_get_quoted_str(char *str, char c)
{
	t_token			*new;
	int				i;
	int				len;
	t_token_type	type;

	i = 0;
	len = 0;
	new = NULL;
	len = lex_quote_len(str, str[i]) - 1;
	type = DOUBLEQUOTE;
	if (c == '\'')
		type = SINGLEQUOTE;
	if (len > 0)
		new = tok_create(str + 1, len, type);
	else
		new = tok_create("\0", 1, STRING);
	return (new);
}

t_token	*ps_parse_quotes(char *str)
{
	int		i;
	t_token	*token;
	t_token	*tmp;

	i = 0;
	token = NULL;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			tmp = ps_get_quoted_str(&(str[i]), str[i]);
			if (!tmp)
				return (NULL);
			tok_add_back(&(token), tmp);
			i += ft_strlen(tmp->value);
		}
		else
		{
			tmp = tok_create(&(str[i]), ps_get_raw_len(&(str[i])), STRING);
			tok_add_back(&(token), tmp);
			i += ft_strlen(tmp->value) - 1;
		}
		i++;
	}
	return (token);
}

int	ps_expand_and_quotes(t_token *token)
{
	t_token	*str;

	while (token != NULL)
	{
		if (token->type == STRING)
			str = ps_parse_quotes(token->value);
		token = token->next;
	}
	tok_debug(str);
	printf("----------\n");
	tok_free(str);
	return (0);
}

// ps_parse_quotes(token);
// ps_expand_path(str);
// tmp = ps_expand_path(tmp);
