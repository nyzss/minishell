/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:35:32 by okoca             #+#    #+#             */
/*   Updated: 2024/07/08 17:34:48 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_token_type	lex_check_meta()
// {

// }

t_token	*handle_in_redir(char *str)
{
	t_token	*new;
	char	*value;

	value = NULL;
	new = NULL;
	if (str[0] == '<')
	{
		if (str[1] == '<')
		{
			value = ft_strndup(str, 2);
			new = tok_create(value, HEREDOC);
			if (new == NULL || value == NULL)
				return (NULL);
		}
		else
		{
			value = ft_strndup(str, 1);
			new = tok_create(value, OUTFILE);
			if (new == NULL || value == NULL)
				return (NULL);
		}
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

// printf("%c\n", line[i]);
// if (line[i] == '\'' || line[i] == '\"')
// {
// }
