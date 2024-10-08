/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 22:09:15 by okoca             #+#    #+#             */
/*   Updated: 2024/07/18 09:13:39 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Uses ft_strndup but will free str
*/
char	*ps_strndup(char *str, int n)
{
	char	*tmp;

	tmp = str;
	str = ft_strndup(str, n);
	free(tmp);
	return (str);
}

/*
* Uses ft_strjoin but will free s1
* or return back s1 if s2 is NULL
*/
char	*ps_strjoin(char *s1, char *s2)
{
	char	*new;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s2 == NULL)
		return (s1);
	else if (s1 == NULL)
		return (ft_strdup(s2));
	new = ft_strjoin(s1, s2);
	free(s1);
	return (new);
}

int	ps_check_all_null(t_token *token)
{
	int	i;

	i = 1;
	while (token)
	{
		if (token->value)
			i = 0;
		token = token->next;
	}
	return (i);
}
