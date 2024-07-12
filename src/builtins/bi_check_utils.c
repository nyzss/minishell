/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_check_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 22:42:10 by okoca             #+#    #+#             */
/*   Updated: 2024/07/12 22:46:38 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_check_id(char *id)
{
	int	i;

	i = 0;
	if (!*id)
		return (0);
	while (id[i])
	{
		if (i == 0 && ft_isalpha(id[i]) == 0 && id[i] != '_')
			return (0);
		if (ft_isalnum(id[i]) == 0 && id[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
