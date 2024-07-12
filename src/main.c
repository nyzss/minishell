/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:23:11 by okoca             #+#    #+#             */
/*   Updated: 2024/07/12 17:34:47 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipeline(t_ctx *ctx, char *line)
{
	t_token	*token;

	(void)ctx;
	token = lexer(ctx, line);
	if (token == NULL)
		return (1);
	if (parser(&token) != 0)
	{
		tok_free(token);
		return (1);
	}
	ctx->exec = builder(token);
	ctx->exec_count = br_lstsize(ctx->exec);
	exec(ctx);
	// br_debug(exec_var);
	// tok_debug(token);
	ms_clear(ctx, token);
	ctx->exec_count = 0;
	return (0);
}

int	handle_loop(t_ctx *ctx)
{
	char	*line;

	line = NULL;
	signal(SIGINT, sig_main_sigint);
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

// char *e = "ABCD";
// env_add_back(&(ctx->envp), env_create(env_get_id(e), env_get_value(e), e));
//	for (t_env *env = ctx->envp; env != NULL; env = env->next)
//	{
//		printf("--------------\n");
//		printf("ID:    [%s]\n", env->id);
//		printf("VALUE: [%s]\n", env->value);
//		printf("RAW:   [%s]\n", env->raw);
// 	}