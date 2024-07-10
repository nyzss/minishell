/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:37:42 by okoca             #+#    #+#             */
/*   Updated: 2024/07/10 17:40:25 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	br_handle_redirs(t_exec *exec, t_token *token)
{
	t_filenames	*filenames;
	t_filenames	*tmp;

	filenames = NULL;
	if (token->next && token->next->value != NULL
		&& (token->type == APPEND || token->type == HEREDOC
			|| token->type == INFILE || token->type == OUTFILE))
	{
		if (token->type == HEREDOC)
			exec->here_doc = 1;
		tmp = fn_create(token->next->value, token->type);
		if (!tmp)
		{
			fn_free(filenames);
			return (-1);
		}
		fn_add_back(&(filenames), tmp);
		return (1);
	}
	return (0);
}

t_exec	*builder(t_token *token)
{
	t_exec	*exec;

	exec = br_init();
	if (!exec)
		return (NULL);
	while (token != NULL)
	{
		if (token->type == PIPE)
		{
			exec->next = builder(token->next);
			break ;
		}
		br_handle_redirs(exec, token);
		token = token->next;
	}
	return (exec);
}
