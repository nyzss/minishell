/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:37:42 by okoca             #+#    #+#             */
/*   Updated: 2024/07/12 11:25:08 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	br_handle_redirs(t_exec *exec, t_token *token)
{
	t_filenames	*tmp;

	if (token->next && token->next->value != NULL
		&& (token->type == APPEND || token->type == HEREDOC
			|| token->type == INFILE || token->type == OUTFILE))
	{
		if (token->type == HEREDOC)
			exec->here_doc = 1;
		tmp = fn_create(token->next->value, token->type);
		if (!tmp)
			return (-1);
		fn_add_back(&(exec->redirs), tmp);
		return (1);
	}
	return (0);
}

static int	br_handle_args(t_exec *exec, t_token *token)
{
	t_args	*new;

	new = NULL;
	if (token->type == ARGUMENT)
	{
		new = arg_create(token->value);
		if (!new)
			return (-1);
		arg_add_back(&(exec->args), new);
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
		else if (token->type == COMMAND)
		{
			exec->cmd = ft_strdup(token->value);
			if (!exec->cmd)
				return (NULL);
		}
		br_handle_redirs(exec, token);
		br_handle_args(exec, token);
		token = token->next;
	}
	return (exec);
}
