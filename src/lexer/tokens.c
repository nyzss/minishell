/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:34:48 by okoca             #+#    #+#             */
/*   Updated: 2024/07/09 13:46:26 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tok_free(t_token *token)
{
	t_token	*tmp;

	while (token != NULL)
	{
		tmp = token;
		if (token->value)
		{
			free(token->value);
			token->value = NULL;
		}
		token = token->next;
		free(tmp);
	}
}

/*
* takes a value, and a token_type
* then strndup's the value for 'n' characters.
* for ex:
* tok_create("hello", 3, STRING)
* -> value: hel, type: STRING
*/
t_token	*tok_create(char *value, int n, t_token_type type)
{
	t_token	*token;
	char	*new;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	new = ft_strndup(value, n);
	if (!new)
	{
		free(token);
		return (NULL);
	}
	token->value = new;
	token->type = type;
	token->next = NULL;
	return (token);
}

t_token	*tok_last(t_token *token)
{
	while (token->next != NULL)
		token = token->next;
	return (token);
}

int	tok_add_back(t_token **head, t_token *new)
{
	if (new == NULL)
		return (1);
	if (*head == NULL)
		*head = new;
	else
		tok_last(*head)->next = new;
	return (0);
}

void	tok_debug(t_token *token)
{
	char	token_str[12][30];

	ft_strlcpy(token_str[INFILE], "INFILE", 30);
	ft_strlcpy(token_str[OUTFILE], "OUTFILE", 30);
	ft_strlcpy(token_str[HEREDOC], "HEREDOC", 30);
	ft_strlcpy(token_str[APPEND], "APPEND", 30);
	ft_strlcpy(token_str[PIPE], "PIPE", 30);
	ft_strlcpy(token_str[STRING], "STRING", 30);
	ft_strlcpy(token_str[SINGLEQUOTE], "SINGLEQUOTE", 30);
	ft_strlcpy(token_str[DOUBLEQUOTE], "DOUBLEQUOTE", 30);
	ft_strlcpy(token_str[QUOTE], "QUOTE", 30);
	ft_strlcpy(token_str[COMMAND], "COMMAND", 30);
	ft_strlcpy(token_str[FILENAME], "FILENAME", 30);
	ft_strlcpy(token_str[ARGUMENT], "ARGUMENT", 30);
	while (token != NULL)
	{
		printf("(%s) [%s]\n", token_str[token->type], token->value);
		token = token->next;
	}
}
