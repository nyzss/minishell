/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:01:24 by okoca             #+#    #+#             */
/*   Updated: 2024/07/12 16:02:57 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_ctx	t_ctx;
typedef struct s_env	t_env;

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

/* exec main */
int		exec(t_ctx *ctx);
int		exec_1(t_ctx *ctx, int exec_no, int *fd_in, int *fd_out);
int		exec_2(t_ctx *ctx, int exec_no, int *fd_in, int *fd_out);
void	exe_get_stdfds(t_ctx *ctx);
void	exe_reset_stdfds(t_ctx *ctx);
void	exe_wait_all(int rep, unsigned int *exit_code);

/* fdio utils*/
int		exe_init_fdio(int *fd_in, int *fd_out, t_exec *exec, int fd_stdin);
int		exe_is_here_doc(t_exec *exec, int fd_stdin);
void	exe_init_here_doc(char *file, char *eof, int fd_stdin);
int		exe_handle_files(int *fd_in, int *fd_out, t_exec *exec);
int		exe_check_fdio(int *fd_in, int *fd_out, char *file);

/* pipe utils */
void	exe_create_pipe(int *fd_out, int fd_pipe[2]);
int		exe_redir_fdio(int *fd_in, int *fd_out, int pipe[2], t_exec *exec);
void	exe_do_child(t_exec *exec, t_env *env, int fd_in);
void	exe_dup2_close(int fd1, int fd2);
int		exe_is_abs_path(char *file);

/* child_utils */
int		exe_do_exec(char *cmd, t_args *args, t_env *env);
char	*exe_get_path(char *file, t_env *env);
char	*exe_get_exec(char **paths, char *file);
char	**exe_get_allpaths(t_env *env);
char	**exe_get_cmds(char *cmd, t_args *args);
char	**exe_get_envs(t_env *env);

/* err_utils */
void	exe_err1_open(int err_no, char *file);
void	exe_err2_pipe(int err_no);
void	exe_err3_fork(int err_no);
void	exe_err4_exec(char *path, int err_no);

#endif