# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okoca <okoca@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/08 11:20:19 by okoca             #+#    #+#              #
#    Updated: 2024/07/16 10:50:59 by okoca            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell

SRCS_M		= main.c

SRCS_BT		= bi_func.c bi_func_utils.c bi_func_utils2.c bi_err_utils.c bi_check_utils.c

SRCS_EX 	= exec.c exec_fdio_utils.c exec_pipe_utils.c exec_child_utils.c exec_err_utils.c

SRCS_LEX 	= lexer.c tokens.c lex_helper.c

SRCS_PAR 	= parser.c expansion.c quotes.c parser_helper.c expand_helper.c heredoc.c

SRCS_UTI 	= utils.c helper.c env.c env_helper.c

SRCS_BLD 	= builder.c builder_helper.c filenames.c args.c

SRCS_SIG 	= signal.c

SRC 		= src/

BUILTINS_PATH	= src/builtins/
EXEC_PATH	= src/exec/
LEXER_PATH	= src/lexer/
PARSER_PATH	= src/parser/
UTILS_PATH	= src/utils/
BUILDER_PATH	= src/builder/
SIGNAL_PATH	= src/signals/

SRCS		= $(addprefix $(SRC), $(SRCS_M)) \
		  $(addprefix $(BUILTINS_PATH), $(SRCS_BT)) \
		  $(addprefix $(EXEC_PATH), $(SRCS_EX)) \
		  $(addprefix $(LEXER_PATH), $(SRCS_LEX)) \
		  $(addprefix $(PARSER_PATH), $(SRCS_PAR)) \
		  $(addprefix $(UTILS_PATH), $(SRCS_UTI)) \
		  $(addprefix $(BUILDER_PATH), $(SRCS_BLD)) \
		  $(addprefix $(SIGNAL_PATH), $(SRCS_SIG)) \

# F_PATH		= src/

# SRCS		= $(addprefix $(F_PATH), $(SRCS_F))

OBJS		= $(SRCS:.c=.o)

HEAD		= includes/

CFLAGS		= -Wall -Wextra -Werror -g

CC		= cc

LIBFT_PATH	= libft/
LIBFT_H_PATH	= libft/includes/
LIBFT		= $(LIBFT_PATH)libft.a

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(HEAD) -I$(LIBFT_H_PATH) -c $< -o $@

clean: libft-clean root-clean

libft-clean:
	$(MAKE) -C $(LIBFT_PATH) clean

root-clean:
	rm -f $(OBJS)

fclean: libft-fclean root-fclean

libft-fclean:
	$(MAKE) -C $(LIBFT_PATH) fclean

root-fclean: root-clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re libft libft-clean libft-fclean root-clean root-fclean
