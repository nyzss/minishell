/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:57:50 by tsuchen           #+#    #+#             */
/*   Updated: 2024/05/15 10:57:54 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
#include <unistd.h>
#include <ctype.h>
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	main(int ac, char *av[])
{
	if ((ac != 2) || (ft_strlen(av[1]) != 1))
	{
		write(1, "Input Error\n", 12);
		return (0);
	}
	int	output;

	output = ft_isprint(*(av[1]));
	if (output == 1)
		write(1, "1", 1);
	else
		write(1, "0", 1);
	if (isprint(*(av[1])) == 1)
		write(1, "\n1", 2);
	else
		write(1, "\n0", 2);
	return (0);
}*/
