/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 22:09:15 by okoca             #+#    #+#             */
/*   Updated: 2024/07/09 22:14:56 by okoca            ###   ########.fr       */
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

	if (s2 == NULL)
		return (s1);
	new = ft_strjoin(s1, s2);
	free(s1);
	return (new);
}

char	*ps_getenv(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	name = ft_strndup(str, i);
	return (name);
}
