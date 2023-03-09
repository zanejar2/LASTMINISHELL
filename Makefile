# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 22:41:40 by zanejar           #+#    #+#              #
#    Updated: 2023/03/09 07:36:40 by zanejar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

SOURCE = src/main.c src/lexer.c src/lexer2.c src/token.c src/lexer3.c \
		src/checker.c src/checker2.c src/parser.c src/parser2.c \
		src/utils.c src/utils2.c src/parser3.c src/utils3.c src/utils4.c \
		src/utils5.c execution/builtins.c execution/builtins_tools.c \
		execution/nopipe.c execution/m_signal.c execution/builtins_tools2.c \
		execution/herdoc.c execution/outils.c execution/builtins_tools3.c \
		execution/builtins_tools4.c src/utils6.c execution/m_signal2.c \
		execution/exec1.c execution/exec2.c execution/exec3.c \
		execution/exec4.c execution/exec5.c src/funcs.c

RDLINE = -lreadline -L /Users/mabdenna/goinfre/homebrew/opt/readline/lib -I /Users/mabdenna/goinfre/homebrew/opt/readline/include


RM = rm -Rf

all :		$(NAME)

$(NAME):	$(SOURCE)
			$(CC) $(CFLAGS) $(RDLINE) $(SOURCE) -o $(NAME)

clean:
			$(RM) $(OBJ)

fclean: 	clean
			$(RM) $(NAME)

re: 		fclean all

.PHONY:		all clean fclean re