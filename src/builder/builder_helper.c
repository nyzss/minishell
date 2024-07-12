/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:41:09 by okoca             #+#    #+#             */
/*   Updated: 2024/07/12 11:26:32 by tsuchen          ###   ########.fr       */
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

void	br_free(t_exec *exec)
{
	t_exec	*tmp;

	while (exec != NULL)
	{
		tmp = exec;
		if (exec->cmd)
			free(exec->cmd);
		if (exec->args)
			arg_free(exec->args);
		if (exec->redirs)
			fn_free(exec->redirs);
		exec = exec->next;
		free(tmp);
	}
}

int	br_lstsize(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec)
	{
		i++;
		exec = exec->next;
	}
	return (i);
}

void	br_debug(t_exec *exec)
{
	t_args		*args;
	t_filenames	*filenames;

	while (exec != NULL)
	{
		printf(MAGENTA_A "----------- EXEC ----------\n");
		printf(BLUE_A);
		args = exec->args;
		filenames = exec->redirs;
		printf("CMD: [%s]\n", exec->cmd);
		printf("HEREDOC: [%d]\n", exec->here_doc);
		printf("ARGS: [%p]\n", exec->args);
		printf("FILENAMES: [%p]\n", exec->redirs);
		if (args != NULL)
			printf("#ARGS\n");
		printf(C_RESET);
		while (args != NULL)
		{
			printf("---->[%s]\n", args->value);
			args = args->next;
		}
		printf(BLUE_A);
		if (filenames != NULL)
			printf("#REDIRS\n");
		printf(C_RESET);
		while (filenames != NULL)
		{
			printf("---->[%s]\n", filenames->path);
			printf("---->[%d]\n", filenames->type);
			filenames = filenames->next;
		}
		printf(BLUE_A);
		printf("NEXT: [%p]\n", exec->next);
		if (exec->next == NULL)
			printf(MAGENTA_A "-------------------\n" C_RESET);
		exec = exec->next;
	}
}
