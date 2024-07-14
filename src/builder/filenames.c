/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filenames.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:00:13 by okoca             #+#    #+#             */
/*   Updated: 2024/07/14 10:11:30 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fn_free(t_filenames *filenames)
{
	t_filenames	*tmp;

	while (filenames != NULL)
	{
		tmp = filenames;
		if (filenames->path)
			free(filenames->path);
		filenames = filenames->next;
		free(tmp);
	}
}

/*
* will do the strdup on the path, just pass in a string
*/
t_filenames	*fn_create(char *path, t_token_type type)
{
	t_filenames	*filename;
	char		*new;

	filename = malloc(sizeof(t_filenames));
	if (filename == NULL)
		return (NULL);
	new = ft_strdup(path);
	if (!new)
	{
		free(filename);
		return (NULL);
	}
	filename->path = new;
	filename->type = type;
	filename->next = NULL;
	return (filename);
}

t_filenames	*fn_last(t_filenames *filename)
{
	while (filename->next != NULL)
		filename = filename->next;
	return (filename);
}

int	fn_add_back(t_filenames **head, t_filenames *new)
{
	if (new == NULL)
		return (1);
	if (*head == NULL)
		*head = new;
	else
		fn_last(*head)->next = new;
	return (0);
}

int	fn_lstsize(t_filenames *filename)
{
	int	i;

	i = 0;
	while (filename)
	{
		i++;
		filename = filename->next;
	}
	return (i);
}
