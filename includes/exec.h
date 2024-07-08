/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:01:24 by okoca             #+#    #+#             */
/*   Updated: 2024/07/08 14:03:32 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

int     exec(t_ctx *ctx);
int		handle_infile(t_filenames *redirs);
int		handle_outfile(t_filenames *redirs);
int		init_here_doc(char *file, char *eof);
void    set_init_input(int *fd_in, t_filenames *redirs);
void    set_init_output(int *fd_out, t_filenames *redirs);

#endif