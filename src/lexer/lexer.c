/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:35:32 by okoca             #+#    #+#             */
/*   Updated: 2024/07/09 08:32:48 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_token	*handle_in_redir(char *str)
{
	t_token			*new;
	t_token_type	type;

	new = NULL;
	type = lex_get_type(str);
	if (type == HEREDOC)
	{
		new = tok_create(str, 2, HEREDOC);
		if (new == NULL)
			return (NULL);
	}
	else if (type == INFILE)
	{
		new = tok_create(str, 1, INFILE);
		if (new == NULL)
			return (NULL);
	}
	return (new);
}

t_token	*lexer(char *line)
{
	t_token	*token;
	t_token	*tmp;
	int		i;

	i = 0;
	token = NULL;
	tmp = NULL;
	while (line[i])
		i++;
	// while (line[i])
	// {
	// 	// tmp = handle_in_redir();
	// 	else if (line[i] == '>')
	// 	{
	// 		if (line[i + 1] == '>')
	// 		{
	// 			value = ft_strndup(&(line[i]), 2);
	// 			tmp = tok_create(value, APPEND);
	// 		}
	// 		else
	// 		{
	// 			value = ft_strndup(&(line[i]), 1);
	// 			tmp = tok_create(value, OUTFILE);
	// 		}
	// 		i += ft_strlen(value);
	// 	}
	// 	i++;
	// }
	return (token);
}
