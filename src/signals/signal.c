/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:46:40 by okoca             #+#    #+#             */
/*   Updated: 2024/07/15 08:39:05 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_init_signals(void)
{
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, sig_quit_handler);
}

void	sig_int_handler(int status)
{
	(void)status;
	if (g_signal != 1)
	{
		g_signal = 130;
		write(STDIN_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
// printf("g_signal: %d\n", g_signal);

void	sig_quit_handler(int status)
{
	(void)status;
}

void	sig_handle_heredoc(int status)
{
	(void)status;
}
// read(STDIN_FILENO, "\0", 1);
// write(2, "\n", 1);
// printf("CALLED HEREDOC: %d\n", status);
