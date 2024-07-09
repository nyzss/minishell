/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:01:24 by okoca             #+#    #+#             */
/*   Updated: 2024/07/09 08:41:52 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_args
{
	char			*value;
	struct s_args	*next;
}	t_args;

typedef struct s_filenames
{
	char				*path;
	t_token_type		type;
	struct s_filenames	*next;
}	t_filenames;

typedef struct s_exec
{
	char			*cmd;
	t_args			*args;
	t_filenames		*redirs;
	struct s_exec	*next;
}	t_exec;

typedef struct s_ctx
{
	int				def_in;
	int				def_out;
	t_exec			*exec;
	char			**env;
	unsigned int	exit_code;
}	t_ctx;

int     exec(t_ctx *ctx);
int		handle_infile(t_filenames *redirs);
int		handle_outfile(t_filenames *redirs);
int		init_here_doc(char *file, char *eof);
void    set_init_input(int *fd_in, t_filenames *redirs);
void    set_init_output(int *fd_out, t_filenames *redirs);
void    do_child(t_exec *exec, char **env, unsigned int *exit_code);

#endif
