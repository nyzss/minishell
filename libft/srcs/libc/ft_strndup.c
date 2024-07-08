/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:33:59 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/08 17:01:17 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, int nb)
{
	char	*new;
	int		i;
	int		len;

	i = 0;
	if (!str || nb <= 0)
		return (NULL);
	if ((int)ft_strlen(str) <= nb)
		len = ft_strlen(str);
	else
		len = nb;
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (str[i] && i < nb)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char	*src = "Source";
	char	*dup_t;
	char	*dup_r;

	dup_t = ft_strdup(src);
	if (!dup_t)
		return (0);
	dup_r = strdup(src);
	if (!dup_r)
		return (0);
	printf("Duplicate test: %s\n", dup_t);
	printf("Duplicate real: %s\n", dup_r);
	free(dup_t);
	free(dup_r);
	return (0);
}*/
