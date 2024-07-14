/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:44:09 by okoca             #+#    #+#             */
/*   Updated: 2024/07/14 10:11:07 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arg_free(t_args *args)
{
	t_args	*tmp;

	while (args != NULL)
	{
		tmp = args;
		if (args->value)
			free(args->value);
		args = args->next;
		free(tmp);
	}
}

/*
* will do the strdup on the path, just pass in a string
*/
t_args	*arg_create(char *value)
{
	t_args	*args;
	char	*new;

	args = malloc(sizeof(t_args));
	if (args == NULL)
		return (NULL);
	new = ft_strdup(value);
	if (!new)
	{
		free(args);
		return (NULL);
	}
	args->value = new;
	args->next = NULL;
	return (args);
}

t_args	*arg_last(t_args *args)
{
	while (args->next != NULL)
		args = args->next;
	return (args);
}

int	arg_add_back(t_args **head, t_args *new)
{
	if (new == NULL)
		return (1);
	if (*head == NULL)
		*head = new;
	else
		arg_last(*head)->next = new;
	return (0);
}

int	arg_lstsize(t_args *args)
{
	int	i;

	i = 0;
	while (args)
	{
		i++;
		args = args->next;
	}
	return (i);
}
