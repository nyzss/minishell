/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:10:09 by okoca             #+#    #+#             */
/*   Updated: 2024/07/09 16:01:27 by okoca            ###   ########.fr       */
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

char	*ps_parse_quotes(char *str)
{
	t_token	*list;
	t_token	*tmp;
	int		i;
	int		len;
	int		str_len;

	i = 0;
	len = 0;
	tmp = NULL;
	list = NULL;
	str_len = ft_strlen(str);
	while (i < str_len)
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			len = lex_quote_len(&(str[i]), str[i]) - 1;
			if (len > 0)
			{
				if (str[i] == '\'')
					tmp = tok_create(&(str[i + 1]), len, SINGLEQUOTE);
				else
					tmp = tok_create(&(str[i + 1]), len, DOUBLEQUOTE);
				tok_add_back(&(list), tmp);
				i += ft_strlen(tmp->value);
			}
			else
			{
				tmp = tok_create("\0", 1, STRING);
				tok_add_back(&(list), tmp);
				i++;
			}
		}
		else
		{
			tmp = tok_create(&(str[i]), ps_get_raw_len(&(str[i])), STRING);
			tok_add_back(&(list), tmp);
			i += ft_strlen(tmp->value);
		}
		i++;
	}
	printf(" ------------------- ps_parse_quote:\n");
	tok_debug(list);
	printf(" -------------------\n");
	tok_free(list);
	return (NULL);
}

int	ps_expand_and_quotes(t_token *token)
{
	char	*tmp;

	(void)tmp;
	while (token != NULL)
	{
		if (token->type == STRING)
		{
			// tmp = ps_parse_quotes(token->value);
			// if (tmp == NULL)
			// 	return (1);
			// token->value = tmp;
		}
		token = token->next;
	}
	return (0);
}

// ps_parse_quotes(token);
// ps_expand_path(str);
// tmp = ps_expand_path(tmp);
