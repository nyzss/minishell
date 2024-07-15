/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:16:07 by okoca             #+#    #+#             */
/*   Updated: 2024/07/15 17:48:07 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ps_handle_heredoc(t_token *token)
{
	char	*filename;
	char	*eof;

	while (token != NULL)
	{
		if (token->type == HEREDOC)
		{
			filename = ms_generate_random(token->next->value);
			eof = token->next->value;
			printf("filename: %s\n", filename);
			exe_init_here_doc(filename, eof, STDIN_FILENO);
			token->next->value = filename;
			free(eof);
		}
		token = token->next;
	}
	return (0);
}