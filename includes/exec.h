/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:01:24 by okoca             #+#    #+#             */
/*   Updated: 2024/07/10 08:26:33 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_ctx	t_ctx;

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
	int				here_doc;
}	t_exec;

int     exec(t_ctx *ctx);
void	get_stdfds(t_ctx *ctx);
void	reset_stdfds(t_ctx *ctx);
void	create_pipe(int *fd_out, int fd_pipe[2], t_exec *exec);
int		init_fdio(int *fd_in, int *fd_out, t_exec *exec, int fd_stdin);
int		is_here_doc(t_exec *exec, int fd_stdin);
void	init_here_doc(char *file, char *eof, int fd_stdin);
int		handle_files(int *fd_in, int *fd_out, t_exec *exec);
int		check_fdio(int *fd_in, int *fd_out, char *file, t_exec *exec);
int		redirect_fdio(int *fd_in, int *fd_out, int fd_pipe[2], t_exec *exec);
void    do_child(t_exec *exec, char **env, unsigned int *exit_code);
void	dup2_close(int fd1, int fd2);

/* err_utils*/
void	ft_err1_open(int err_no, char *file, t_exec *exec);
void	ft_err2_pipe(int err_no, t_exec *exec);
void	ft_err3_fork(int err_no, t_exec *exec);

#endif