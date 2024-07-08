/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:41:15 by okoca             #+#    #+#             */
/*   Updated: 2024/07/08 14:49:56 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	todo(char *what_to_do)
{
	(void)what_to_do;
}

t_ctx	*init_ctx(char **envp)
{
	t_ctx	*ctx;

	ctx = malloc(sizeof(t_ctx));
	if (!ctx)
		return (NULL);
	ctx->def_in = STDIN_FILENO;
	ctx->def_in = STDOUT_FILENO;
	ctx->env = envp;
	ctx->exec = NULL;
	ctx->exit_code = 0;
	return (ctx);
}

void	free_all(t_ctx *ctx)
{
	if (ctx)
	{
		if (ctx->exec)
		{
			todo("Free all exec");
		}
		free(ctx);
	}
}
