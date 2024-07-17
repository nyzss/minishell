/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:49:23 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/17 15:48:00 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

static int	ft_count_digit(long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count += 1;
		n *= -1;
	}
	if (n == 0)
		count += 1;
	while (n > 0)
	{
		count += 1;
		n /= 10;
	}
	return (count);
}

static long	ft_power(long base, int pwr, long output)
{
	if (pwr == 0)
		return (output);
	else
		return (ft_power(base, pwr - 1, output * base));
}

char	*ft_ltoa(long n)
{
	char	*str;
	int		size;
	int		i;

	if (n == LONG_MIN)
		return (ft_strdup("-9223372036854775808"));
	size = ft_count_digit(n);
	str = (char *)malloc((size + 1) * sizeof(char));
	if (!str)
		return (0);
	i = -1;
	if (n < 0)
	{
		str[++i] = '-';
		n *= -1;
	}
	while (++i < size)
	{
		str[i] = (n / ft_power(10, size - i - 1, 1)) + '0';
		n %= ft_power(10, size - i - 1, 1);
	}
	str[i] = '\0';
	return (str);
}
/* Note
 * 1. if n exceed MAX_INT or MIN_INT, the output will overflow
 * 2. if malloc failed, return NULL
 */
/*
#include <stdio.h>

int	main(int ac, char *av[])
{
	if (ac != 2)
		return (0);
	int	nb;
	char	*str;

	nb = atoi(av[1]);
	str = ft_itoa(nb);
	printf("nbr: %d | str: %s\n", nb, str);
	free(str);
	return (0);
}*/