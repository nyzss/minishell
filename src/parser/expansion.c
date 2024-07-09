/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:33:35 by okoca             #+#    #+#             */
/*   Updated: 2024/07/09 22:20:10 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ps_convert_to_env(char *str, char *found)
{
	char	*tmp;
	char	*path;

	tmp = ft_strndup(str, found - str);
	if (!tmp)
		return (NULL);
	path = ps_getenv(found);
	tmp = ps_strjoin(tmp, getenv(path));
	if (!tmp)
	{
		free(path);
		return (NULL);
	}
	tmp = ps_strjoin(tmp, str + ft_strlen(path));
	free(path);
	return (tmp);
}

int	ps_handle_env(t_token *token)
{
	char	*str;
	char	*tmp;
	char	*found;

	str = token->value;
	while (1)
	{
		found = ft_strrchr(str, '$');
		if (found == NULL)
			break ;
		tmp = str;
		str = ps_convert_to_env(str, found);
		free(tmp);
		if (!str)
			return (-1);
	}
	token->value = str;
	return (0);
}

int	ps_expand_env(t_token *token)
{
	while (token != NULL)
	{
		if (token->type == STRING || token->type == DOUBLEQUOTE)
			ps_handle_env(token);
		token = token->next;
	}
	return (0);
}