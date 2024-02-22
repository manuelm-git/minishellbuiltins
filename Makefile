# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 15:43:04 by mbraga-s          #+#    #+#              #
#    Updated: 2024/02/16 12:45:44 by mbraga-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = testing ./srcs/utils ./srcs/builtins

SRCS_LIBFT = ft_bzero ft_calloc ft_split ft_strlcpy\
	ft_strlen ft_substr ft_lstadd_back ft_lstnew ft_lstlast\
	ft_strncmp ft_strdup ft_memcpy ft_strjoin ft_isdigit \
	ft_atoi

SRCS_EXECUTION = executor forks ex_utils1 ex_utils2

SRCS_PARSING = lexer parser expander

LIB = $(NAME).a

EXEC_PATH = ./srcs/execution

PARSE_PATH = ./srcs/parsing

LIBFT_PATH = ./libft

EXEC = $(addprefix $(EXEC_PATH)/, $(SRCS_EXECUTION))

PARSE = $(addprefix $(PARSE_PATH)/, $(SRCS_PARSING))

LIBFT = $(addprefix $(LIBFT_PATH)/, $(SRCS_LIBFT))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -lreadline -fsanitize=address
RM = rm -fr

all: $(NAME)

$(NAME): $(LIB)
		$(CC) $(CFLAGS) $(LIB) -o $(NAME)

$(LIB): $(SRCS:=.o) $(LIBFT:=.o) $(EXEC:=.o) $(PARSE:=.o)
		ar rc $(LIB) $(SRCS:=.o) $(LIBFT:=.o) $(EXEC:=.o) $(PARSE:=.o)

clean:
	$(RM)	$(SRCS:=.o) $(LIBFT:=.o) $(EXEC:=.o) $(PARSE:=.o)

lclean:
	$(RM)	$(LIB)

fclean: clean lclean
		$(RM)	$(NAME)

re:	fclean	$(NAME)

.PHONY: clean fclean re lclean