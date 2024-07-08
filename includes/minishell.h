/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:23:56 by okoca             #+#    #+#             */
/*   Updated: 2024/07/08 14:49:45 by okoca            ###   ########.fr       */
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

#include "libft.h"

# include "exec.h"
# include "lexer.h"
# include "parser.h"
# include "builtins.h"

# define BLUE_A    "\033[1;34m"
# define MAGENTA_A "\033[1;35m"
# define CYAN_A    "\033[1;36m"

# define ESC_F "\001"
# define ESC_S "\002"
# define C_RESET "\033[0m"

# define PROMPT ESC_F BLUE_A ESC_S "minishell >$ " ESC_F C_RESET ESC_S

// ----------------------- LEXER -----------------------

typedef enum e_token_type
{
	INFILE,
	OUTFILE,
	HEREDOC,
	APPEND,
	PIPE,
	STRING,
	COMMAND,
	FILENAME,
	ARGUMENT
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

// ----------------------- EXEC -----------------------

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

void	todo(char *what_to_do);

t_ctx	*init_ctx(char **envp);

void	free_all(t_ctx *ctx);

#endif