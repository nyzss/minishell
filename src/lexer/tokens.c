/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:34:48 by okoca             #+#    #+#             */
/*   Updated: 2024/07/09 08:34:35 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	token = malloc(sizeof(token));
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
