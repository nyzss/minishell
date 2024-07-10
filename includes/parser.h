/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:01:38 by okoca             #+#    #+#             */
/*   Updated: 2024/07/10 11:45:29 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int		parser(t_token **token);

int		ps_expand_and_quotes(t_token *head);

int		ps_expand_env(t_token *token);

char	*ps_strndup(char *str, int n);

char	*ps_strjoin(char *s1, char *s2);

char	*ps_getenv(char *str);

#endif