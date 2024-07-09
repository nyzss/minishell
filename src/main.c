/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:23:11 by okoca             #+#    #+#             */
/*   Updated: 2024/07/09 13:36:52 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipeline(t_ctx *ctx, char *line)
{
	t_token	*token;

	(void)ctx;
	token = lexer(line);
	if (token == NULL)
		return (1);
	tok_debug(token);
	tok_free(token);
	token = NULL;
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
		else if (check_line(line) == 0)
		{
			add_history(line);
			if (handle_pipeline(ctx, line) != 0)
			{
				free(line);
				return (1);
			}
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
	ctx = init_ctx(envp);
	if (!ctx)
		return (EXIT_FAILURE);
	handle_loop(ctx);
	free_all(ctx);
	return (EXIT_SUCCESS);
}
