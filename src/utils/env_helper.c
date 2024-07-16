/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:47:44 by okoca             #+#    #+#             */
/*   Updated: 2024/07/16 10:51:01 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_default_env(void)
{
	char	*id;
	char	*value;
	t_env	*def;

	id = env_get_id(DEF_ENV);
	value = env_get_value(DEF_ENV);
	def = env_create(id, value, ft_strdup(DEF_ENV));
	return (def);
}
