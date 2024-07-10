/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:43:09 by okoca             #+#    #+#             */
/*   Updated: 2024/07/10 17:41:55 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDER_H
# define BUILDER_H

t_exec		*builder(t_token *token);

t_exec		*br_init(void);

void		br_debug(t_exec *exec);

int			fn_add_back(t_filenames **head, t_filenames *new);

t_filenames	*fn_create(char *path, t_token_type type);

void		fn_free(t_filenames *filenames);

#endif