/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:23:11 by okoca             #+#    #+#             */
/*   Updated: 2024/07/15 13:40:55 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

int	ms_setup_exec(t_ctx *ctx, t_token **token)
{
	ctx->exec = builder(*token);
	if (!ctx->exec)
		return (1);
	ctx->exec_count = br_lstsize(ctx->exec);
	ctx->pids = malloc(sizeof(pid_t) * (ctx->exec_count + 1));
	if (!ctx->pids)
		return (1);
	ctx->pid_count = 0;
	tok_free(*token);
	*token = NULL;
	return (0);
}

int	handle_pipeline(t_ctx *ctx, char *line)
{
	t_token	*token;

	token = lexer(ctx, line);
	free(line);
	if (token == NULL)
		return (1);
	if (parser(&token) != 0)
	{
		tok_free(token);
		return (1);
	}
	if (ms_setup_exec(ctx, &token) != 0)
		return (1);
	exec(ctx);
	ms_clear(ctx, token);
	return (0);
}

int	handle_loop(t_ctx *ctx)
{
	char	*line;

	line = NULL;
	while (1)
	{
		sig_init_signals();
		line = readline(PROMPT);
		if (line == NULL)
			break ;
		else if (ms_check_line(line) == 0)
		{
			add_history(line);
			if (handle_pipeline(ctx, line) != 0)
				ft_putstr_fd("Parsing error!\n", 2);
			line = NULL;
		}
		if (line)
			free(line);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_ctx	*ctx;

	(void)ac;
	(void)av;
	ctx = ms_init_ctx(envp);
	if (!ctx)
		return (EXIT_FAILURE);
	handle_loop(ctx);
	ms_free_all(ctx);
	return (EXIT_SUCCESS);
}
