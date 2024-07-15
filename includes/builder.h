/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:43:09 by okoca             #+#    #+#             */
/*   Updated: 2024/07/15 08:38:41 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDER_H
# define BUILDER_H

/* builder functions fot t_exec */
t_exec		*builder(t_token *token);
t_exec		*br_init(void);
void		br_free(t_exec *exec);
int			br_lstsize(t_exec *exec);
void		br_debug(t_exec *exec);

/* list functions for t_filenames */
void		fn_free(t_filenames *filenames);
t_filenames	*fn_create(char *path, t_token_type type);
t_filenames	*fn_last(t_filenames *filename);
int			fn_add_back(t_filenames **head, t_filenames *new);
int			fn_lstsize(t_filenames *filename);

/* list functions for t_args */
void		arg_free(t_args *args);
t_args		*arg_create(char *value);
t_args		*arg_last(t_args *args);
int			arg_add_back(t_args **head, t_args *new);
int			arg_lstsize(t_args *args);

#endif