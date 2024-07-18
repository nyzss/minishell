/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:35:56 by okoca             #+#    #+#             */
/*   Updated: 2024/07/18 09:11:22 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ps_handle_redir(t_token *token)
{
	if (token && token->type == PIPE)
		return (1);
	while (token != NULL)
	{
		if (token->type == APPEND || token->type == INFILE
			|| token->type == OUTFILE || token->type == HEREDOC)
		{
			if (token->next == NULL || token->next->type != STRING)
				return (1);
			token->next->type = FILENAME;
		}
		else if (token->type == PIPE && token->next == NULL)
			return (1);
		token = token->next;
	}
	return (0);
}

int	ps_handle_cmd(t_token *token)
{
	while (token != NULL)
	{
		if (token->type == STRING)
		{
			token->type = COMMAND;
			while (token != NULL && token->type != PIPE)
			{
				if (token->type == STRING)
					token->type = ARGUMENT;
				token = token->next;
			}
		}
		if (token != NULL)
			token = token->next;
	}
	return (0);
}

int	ps_handle_quotes(t_token *token)
{
	int		i;
	char	*str;

	while (token != NULL)
	{
		if (token->type == STRING)
		{
			i = 0;
			str = token->value;
			while (str[i])
			{
				if (str[i] == '\'' || str[i] == '\"')
				{
					i += lex_quote_len(&(str[i]), str[i]);
					if (str[i] == '\0')
						return (1);
				}
				i++;
			}
		}
		token = token->next;
	}
	return (0);
}

int	ps_remove_null(t_token **head)
{
	t_token	*tmp;
	t_token	*token;

	token = (*head);
	while (token != NULL && token->value == NULL)
	{
		tmp = token;
		token = token->next;
		free(tmp);
	}
	*head = token;
	while (token != NULL && token->next != NULL)
	{
		if (token->next->value == NULL)
		{
			tmp = token->next;
			token->next = token->next->next;
			free(tmp);
		}
		token = token->next;
	}
	return (0);
}

int	parser(t_token **token)
{
	int	err;

	err = 0;
	if (ps_handle_quotes(*token) != 0)
		err = 1;
	else if (ps_expand_and_quotes(*token) != 0)
		err = 1;
	else if (ps_remove_null(token) != 0)
		err = 1;
	else if (ps_check_all_null(*token) != 0)
		err = 2;
	else if (ps_handle_redir(*token) != 0)
		err = 1;
	else if (ps_handle_cmd(*token) != 0)
		err = 1;
	else if (ps_handle_heredoc(*token) != 0)
	{
		ps_unlink_err(*token);
		err = 2;
	}
	return (err);
}
