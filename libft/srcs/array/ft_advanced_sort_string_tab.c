/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_advanced_sort_string_tab.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:08:30 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/11 10:07:12 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

static void	ft_swap_pointer(char **a1, char **a2)
{
	char	*temp;

	temp = *a1;
	*a1 = *a2;
	*a2 = temp;
}

void	ft_advanced_sort_string_tab(char **tab, int (*cmp)(char *, char *))
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 1;
		while (tab[i + j])
		{
			if (cmp(tab[i], tab[i + j]) > 0)
				ft_swap_pointer(&tab[i], &tab[i + j]);
			j++;
		}
		i++;
	}
}
/*
char    **ft_split(char *str, char *charset);
int     ft_arr_len(char **arr);
int	ft_strcmp(char *s1, char *s2);
int	ft_desc(char *s1, char *s2);

int	main(void)
{
	char	*str = "This is a simple test. If it works, it works!";
	char	*charset = " ,!";
	char	**tab;
	int		arr_len;

	tab = ft_split(str, charset);
	arr_len = ft_arr_len(tab);
	printf("==> Before sort string <==\n");
	for (int i = 0; i < arr_len; i++)
		printf("Split str %d is: %s\n", i, tab[i]); 
	ft_advanced_sort_string_tab(tab, &ft_desc);
	printf("==> After sort string <==\n");
	for (int j = 0; j < arr_len; j++)
		printf("Split str %d is: %s\n", j, tab[j]);
	//free mem
	for (int k = 0; k < arr_len; k++)
		free(tab[k]);
	free(tab);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	while ((*s1 || *s2) && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	ft_desc(char *s1, char *s2)
{
	if (ft_strcmp(s1, s2) >= 0)
		return (-1);
	else
		return (1);
}*/
