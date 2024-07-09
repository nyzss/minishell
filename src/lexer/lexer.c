/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:35:32 by okoca             #+#    #+#             */
/*   Updated: 2024/07/09 10:57:33 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Will still return NULL if error,
* since we dont do any explicit pointer access,
* we have no need to check if NULL
*/
t_token	*lex_strtok(char *str)
{
	t_token			*new;
	t_token_type	type;
	int				len;

	new = NULL;
	type = lex_get_type(str);
	len = lex_get_len(str, type);
	new = tok_create(str, len, type);
	return (new);
}

t_token	*lexer(char *line)
{
	t_token	*token;
	t_token	*tmp;
	int		i;

	i = 0;
	token = NULL;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			tmp = lex_strtok(&(line[i]));
			if (tmp == NULL)
			{
				tok_free(token);
				return (NULL);
			}
			tok_add_back(&(token), tmp);
			i += ft_strlen(tmp->value);
		}
		else
			i++;
	}
	return (token);
}
