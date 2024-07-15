/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:01:38 by okoca             #+#    #+#             */
/*   Updated: 2024/07/15 17:17:49 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int		parser(t_token **token);
char	*ps_strndup(char *str, int n);
char	*ps_strjoin(char *s1, char *s2);

int		ps_expand_and_quotes(t_token *head);
int		ps_handle_heredoc(t_token *token);

int		ps_expand_env(t_token *token);
char	*ps_getenv_name(char *str);
char	*ps_get_before_env(char *str, char *found);
char	*ps_get_env_var(char *found, t_ctx *ctx);
char	*ps_get_after_env(char *found);

#endif