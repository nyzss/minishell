/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:23:11 by okoca             #+#    #+#             */
/*   Updated: 2024/07/14 10:09:36 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ctx->exec = builder(token);
	ctx->exec_count = br_lstsize(ctx->exec);
	tok_free(token);
	token = NULL;
	exec(ctx);
	ms_clear(ctx, token);
	ctx->exec_count = 0;
	return (0);
}
// br_debug(ctx->exec);
// tok_debug(token);

int	handle_loop(t_ctx *ctx)
{
	char	*line;

	line = NULL;
	sig_init_signals();
	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
			break ;
		else if (ms_check_line(line) == 0)
		{
			add_history(line);
			if (handle_pipeline(ctx, line) != 0)
				fprintf(stderr, "Parsing error!\n");
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
