/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:23:56 by okoca             #+#    #+#             */
/*   Updated: 2024/07/12 15:19:55 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <ncurses.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line_bonus.h"

# include "lexer.h"
# include "parser.h"
# include "exec.h"
# include "builtins.h"
# include "builder.h"
# include "signals.h"

# define P_NAME "minishell"
# define BLUE_A    "\033[1;34m"
# define MAGENTA_A "\033[1;35m"
# define CYAN_A    "\033[1;36m"

# define ESC_F "\001"
# define ESC_S "\002"
# define C_RESET "\033[0m"

# define PROMPT "\001\033[1;36m\002minishell >$ \001\033[0m\002"

typedef struct s_env
{
	char			*id;
	char			*value;
	char			*raw;
	struct s_env	*next;
}	t_env;

typedef struct s_ctx
{
	int				def_in;
	int				def_out;
	unsigned char	exit_code;
	int				exec_count;
	char			**env;
	t_exec			*exec;
	t_env			*envp;
}	t_ctx;

t_ctx	*ms_init_ctx(char **envp);

void	ms_free_all(t_ctx *ctx);

int		ms_check_line(char *line);

void	ms_clear(t_ctx *ctx, t_token *token);

t_env	*ms_env_dup(char **envp);

void	*ms_free_double(char **value);

t_env	*ms_getenv(char *path, t_env *envp);

t_env	*env_create(char *id, char *value, char *raw);

void	env_free(t_env *env);

int		env_add_back(t_env **head, t_env *new);

t_env	*env_last(t_env *env);

char	*env_get_id(char *raw);

char	*env_get_value(char	*raw);

#endif