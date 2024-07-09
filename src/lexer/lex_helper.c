/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:05:56 by okoca             #+#    #+#             */
/*   Updated: 2024/07/09 11:45:53 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// the i++ before the break is needed in case of: [""grep"" something]
// otherwise it won't include the last quote
int	lex_get_quote_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (str[i + 1] != '\'' && str[i + 1] != '\"')
			{
				if (lex_is_meta_char(str[i + 1]) || str[i + 1] == ' ')
				{
					i++;
					break ;
				}
			}
		}
		i++;
	}
	return (i);
}

int	lex_get_str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
				i++;
		}
		else if (lex_is_meta_char(str[i]) || str[i] == ' ')
			break ;
		i++;
	}
	return (i);
}

int	lex_get_string_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || lex_is_meta_char(str[i]))
			break ;
		i++;
	}
	return (i);
}

int	lex_get_len(char *str, t_token_type type)
{
	int	len;

	len = 0;
	if (type == HEREDOC || type == APPEND)
		len = 2;
	else if (type == INFILE || type == OUTFILE || type == PIPE)
		len = 1;
	else if (type == QUOTE || type == STRING)
		len = lex_get_str_len(str);
	return (len);
}

t_token_type	lex_get_type(char *str)
{
	if (str[0] == '<')
	{
		if (str[1] == '<')
			return (HEREDOC);
		else
			return (INFILE);
	}
	else if (str[0] == '>')
	{
		if (str[1] == '>')
			return (APPEND);
		else
			return (OUTFILE);
	}
	else if (str[0] == '|')
		return (PIPE);
	else if (str[0] == '\'' || str[0] == '\"')
		return (QUOTE);
	return (STRING);
}

int	lex_is_meta_char(char c)
{
	int	found;

	found = 0;
	if (c == '|')
		found = 1;
	else if (c == '<')
		found = 2;
	else if (c == '>')
		found = 3;
	else if (c == '\"')
		found = 4;
	else if (c == '\'')
		found = 5;
	return (found);
}
