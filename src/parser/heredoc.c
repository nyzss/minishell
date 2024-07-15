/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:16:07 by okoca             #+#    #+#             */
/*   Updated: 2024/07/15 23:07:37 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ps_init_here_doc(int fd, char *eof)
{
	char	*line;

	signal(SIGINT, sig_heredoc);
	while (1)
	{
		line = readline("heredoc>");
		if (!line)
			break ;
		if (!ft_strcmp(line, eof) || g_signals.end_heredoc == 1)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	if (g_signals.end_heredoc == 1)
	{
		g_signals.end_heredoc = 0;
		return (1);
	}
	return (0);
}

int	ps_handle_heredoc(t_token *token)
{
	char	*filename;
	char	*eof;
	int		fd;
	int		end;
	t_token	*tok;

	end = 0;
	tok = token;
	while (token != NULL && end == 0)
	{
		if (token->type == HEREDOC)
		{
			filename = ms_generate_random(token->next->value);
			eof = token->next->value;
			printf("filename: %s\n", filename);
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (!fd)
				return (1);
			if (ps_init_here_doc(fd, eof) != 0)
				end = 1;
			close(fd);
			token->next->value = filename;
			free(eof);
		}
		token = token->next;
	}
	if (end)
	{
		while (tok != NULL)
		{
			if (tok->type == HEREDOC
				&& ft_strncmp(tok->next->value, "hd_", 3) == 0)
				unlink(tok->next->value);
			tok = tok->next;
		}
		return (1);
	}
	return (0);
}
