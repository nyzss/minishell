/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:23:11 by okoca             #+#    #+#             */
/*   Updated: 2024/07/08 15:01:48 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_loop(t_ctx *ctx)
{
	char	*line;

	(void)ctx;
	line = NULL;
	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
			break ;
		else if (check_line(line) == 0)
		{
			add_history(line);
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
	handle_loop(ctx);
	free_all(ctx);
	return (0);
}
