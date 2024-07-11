/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:00:41 by okoca             #+#    #+#             */
/*   Updated: 2024/07/11 16:23:04 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_ctx	t_ctx;

typedef enum e_token_type
{
	INFILE,
	OUTFILE,
	HEREDOC,
	APPEND,
	PIPE,
	STRING,
	SINGLEQUOTE,
	DOUBLEQUOTE,
	COMMAND,
	FILENAME,
	ARGUMENT
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_ctx			*ctx;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

t_token			*lexer(t_ctx *ctx, char *line);

t_token			*tok_create(char *value, int n, t_token_type type, t_ctx *ctx);

t_token			*tok_last(t_token *token);

int				tok_add_back(t_token **head, t_token *new);

int				lex_is_meta_char(char c);

t_token_type	lex_get_type(char *str);

int				lex_get_len(char *str, t_token_type type);

int				lex_quote_len(char *str, char quote);

void			tok_debug(t_token *token);

void			tok_free(t_token *token);

#endif