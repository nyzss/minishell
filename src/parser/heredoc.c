/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:16:07 by okoca             #+#    #+#             */
/*   Updated: 2024/07/19 09:41:29 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ps_handle_return(void)
{
	if (g_signals.end_heredoc == 1)
	{
		g_signals.end_heredoc = 0;
		return (1);
	}
	return (0);
}

int	ps_init_here_doc(int fd, char *eof)
{
	char	*line;

	signal(SIGINT, sig_heredoc);
	while (1)
	{
		line = readline("heredoc>");
		if (!line)
		{
			ft_putstr_fd("minishell: here_doc: called end-of-line (ctrl-d)\n",
				2);
			break ;
		}
		if (!ft_strcmp(line, eof) || g_signals.end_heredoc == 1)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (ps_handle_return());
}

void	ps_unlink_err(t_token *token)
{
	while (token)
	{
		if (token->type == N_HEREDOC)
			unlink(token->next->value);
		token = token->next;
	}
}

// printf("filename: %s\n", filename);
int	ps_handle_heredoc(t_token *token)
{
	char	*filename;
	int		fd;
	int		end;

	end = 0;
	while (token != NULL && end == 0)
	{
		if (token->type == HEREDOC)
		{
			filename = ms_generate_random(token->next->value);
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (!fd)
				return (1);
			if (ps_init_here_doc(fd, token->next->value) != 0)
				end = 1;
			close(fd);
			free(token->next->value);
			token->next->value = filename;
			token->type = N_HEREDOC;
		}
		token = token->next;
	}
	return (end);
}
