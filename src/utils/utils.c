/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:41:15 by okoca             #+#    #+#             */
/*   Updated: 2024/07/15 15:09:17 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ctx	*ms_init_ctx(char **envp)
{
	t_ctx	*ctx;

	ctx = malloc(sizeof(t_ctx));
	if (!ctx)
		return (NULL);
	ctx->envp = ms_env_dup(envp);
	if (!ctx->envp)
	{
		free(ctx);
		return (NULL);
	}
	ctx->def_in = STDIN_FILENO;
	ctx->def_in = STDOUT_FILENO;
	ctx->exec = NULL;
	ctx->pids = NULL;
	ctx->exec_count = 0;
	ctx->pid_count = 0;
	ctx->exit_code = 0;
	return (ctx);
}

void	ms_clear(t_ctx *ctx, t_token *token)
{
	if (token)
		tok_free(token);
	if (ctx)
	{
		if (ctx->exec)
		{
			br_free(ctx->exec);
			ctx->exec = NULL;
		}
		if (ctx->pids)
		{
			free(ctx->pids);
			ctx->pids = NULL;
		}
	}
}

void	ms_free_all(t_ctx *ctx)
{
	if (ctx)
	{
		if (ctx->exec)
			br_free(ctx->exec);
		if (ctx->envp)
			env_free(ctx->envp);
		if (ctx->pids)
			free(ctx->pids);
		free(ctx);
	}
	rl_clear_history();
}

int	ms_check_line(char *line)
{
	if (line[0] == '\0')
		return (1);
	return (0);
}
