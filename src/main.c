/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:23:11 by okoca             #+#    #+#             */
/*   Updated: 2024/07/11 21:02:43 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipeline(t_ctx *ctx, char *line)
{
	t_token	*token;
	t_exec	*exec_var;

	(void)ctx;
	token = lexer(ctx, line);
	if (token == NULL)
		return (1);
	if (parser(&token) != 0)
	{
		tok_free(token);
		return (1);
	}
	exec_var = builder(token);
	ctx->exec = exec_var;
	exec(ctx);
	// br_debug(exec_var);
	// tok_debug(token);
	ms_clear(ctx, token);
	return (0);
}

int	handle_loop(t_ctx *ctx)
{
	char	*line;

	line = NULL;
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
		}
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
