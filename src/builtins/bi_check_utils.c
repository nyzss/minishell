/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_check_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 22:42:10 by okoca             #+#    #+#             */
/*   Updated: 2024/07/17 14:21:04 by tsuchen          ###   ########.fr       */
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

int	bi_check_exitcode(char *value)
{
	int		code;
	char	*tmp;

	code = ft_atoi(value);
	tmp = value;
	if ((*tmp == '+' || *tmp == '-') && *(tmp + 1))
		tmp++;
	if (ft_strlen(tmp) > 19 || ft_strcmp(tmp, "9223372036854775807") > 0)
	{
		bi_err_exit(value);
		return (2);
	}
	while (*tmp)
	{
		if (!ft_isdigit(*tmp++))
		{
			bi_err_exit(value);
			return (2);
		}
	}
	return (code);
}
