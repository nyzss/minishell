/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:02:35 by okoca             #+#    #+#             */
/*   Updated: 2024/07/12 15:22:12 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_env	t_env;

/* Built-in handler */
int		bi_do_builtin(char *cmd, t_args *args, t_env **env);
int		bi_is_builtin(char *cmd);

/* Built-in Functions */
int		bi_echo(t_args *args);
int		bi_cd(t_args *args, t_env *env);
int		bi_pwd(t_args *args);
int		bi_exit(t_args *args);
int		bi_env(t_args *args, t_env *env);
int		bi_export(t_args *args, t_env **env);
int		bi_unset(t_args *args, t_env **env);

/* helper functions for export and unset */
int		bi_print_export(t_env *env);
int		bi_add_var(t_args *args, t_env **env);
t_env	*bi_get_var(char *var, t_env *env);
int		bi_del_var(t_args *args, t_env **env);

/* error utils */
void	bi_err_cd(int err_no, char *file);
void	bi_err_pwd(char *option);
int		bi_err_export(char *var);
void	bi_err_exit(char *val);
void	bi_err_env(char *file);

#endif
