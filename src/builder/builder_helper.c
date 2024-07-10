/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:41:09 by okoca             #+#    #+#             */
/*   Updated: 2024/07/10 17:02:16 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*br_init(void)
{
	t_exec	*new;

	new = malloc(sizeof(t_exec));
	if (!new)
		return (NULL);
	new->args = NULL;
	new->cmd = NULL;
	new->here_doc = 0;
	new->redirs = NULL;
	new->next = NULL;
	return (new);
}

void	br_debug(t_exec *exec)
{
	t_args		*args;
	t_filenames	*filenames;

	while (exec != NULL)
	{
		args = exec->args;
		filenames = exec->redirs;
		printf("CMD: [%s]\n", exec->cmd);
		printf("--ARGS--\n");
		while (args != NULL)
		{
			printf("\t[%s]\n", args->value);
			args = args->next;
		}
		printf("--REDIRS--\n");
		while (filenames != NULL)
		{
			printf("\t[%s]\n", filenames->path);
			printf("\t[%d]\n", filenames->type);
			filenames = filenames->next;
		}
		printf("HEREDOC: [%d]\n", exec->here_doc);
		printf("NEXT: [%p]\n", exec->next);
		exec = exec->next;
	}
}
