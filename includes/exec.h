/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:01:24 by okoca             #+#    #+#             */
/*   Updated: 2024/07/10 11:35:32 by tsuchen          ###   ########.fr       */
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
void	exe_get_stdfds(t_ctx *ctx);
void	exe_reset_stdfds(t_ctx *ctx);
void	exe_create_pipe(int *fd_out, int fd_pipe[2]);
int		exe_init_fdio(int *fd_in, int *fd_out, t_exec *exec, int fd_stdin);
int		exe_is_here_doc(t_exec *exec, int fd_stdin);
void	exe_init_here_doc(char *file, char *eof, int fd_stdin);
int		exe_handle_files(int *fd_in, int *fd_out, t_exec *exec);
int		exe_check_fdio(int *fd_in, int *fd_out, char *file);
int		exe_redirect_fdio(int *fd_in, int *fd_out, int fd_pipe[2], t_exec *exec);
void    exe_do_child(t_exec *exec, char **env, int fd_in);
int		exe_do_exec(char *cmd, t_args *args, char **env);
char	*exe_get_path(char *file, char **env);
char	*exe_get_exec(char **paths, char *file);
char	**exe_get_allpaths(char **env);
char	**exe_get_cmd(char *cmd, t_args *args);
void	exe_dup2_close(int fd1, int fd2);
void	exe_wait_all(int rep, unsigned int *exit_code);
int		exe_is_abs_path(char *file);

/* err_utils*/
void	exe_free_all(char **arr);
void	exe_err1_open(int err_no, char *file);
void	exe_err2_pipe(int err_no);
void	exe_err3_fork(int err_no);
void	exe_err4_exec(char *path, int err_no);

#endif