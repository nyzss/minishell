/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:16:07 by okoca             #+#    #+#             */
/*   Updated: 2024/07/15 17:33:17 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ps_handle_heredoc(t_token *token)
{
	char	*filename;

	while (token != NULL)
	{
		if (token->type == HEREDOC)
		{
			filename = ms_generate_random(token->next->value);
			printf("filename: %s\n", filename);
			free(filename);
		}
		token = token->next;
	}
	return (0);
}