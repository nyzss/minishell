/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:34:48 by okoca             #+#    #+#             */
/*   Updated: 2024/07/08 15:55:42 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tok_create(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(token));
	if (token == NULL)
		return (NULL);
	token->value = value;
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
