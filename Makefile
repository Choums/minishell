# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/30 20:18:17 by tdelauna          #+#    #+#              #
#    Updated: 2022/07/22 18:41:43 by chaidel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    	=	minishell

SRCDIR		=	./src
INCDIR		=	./includes
OBJDIR		=	obj
LEXERDIR	=	obj/lexer
PARSEDIR	=	obj/parsing
GNLDIR		=	obj/gnl
OTHERDIR	=	obj/other

SRC			=	main.c\
				env.c\
				path.c\
				affichage.c\
				builtin.c\
				echo.c\
				lst_management.c\
				var_management.c\
				change_dir.c\
				goto_cd.c\
				utils.c\
				pipes.c\
				exec.c\
				check_exec.c\
				check_proc.c\
				heredoc.c\
				exporter.c\
				print_export.c\
				errors.c\
				redir.c\
				redir_file.c\
				exiting.c\
				dollars.c\
				other/free.c\
				other/signal.c\
				gnl/get_next_line.c\
				gnl/get_next_line_utils.c\
				lexer/parse_quote.c\
				lexer/parse_back.c\
				lexer/expand.c\
				lexer/expand_utils.c\
				lexer/verif_line.c\
				lexer/verif_line_utils.c\
				parsing/command_utils.c\
				parsing/command.c\
				parsing/parsing.c\
				parsing/redirection_utils.c\
				parsing/redirection.c\
				parsing/split_pipe.c\
				parsing/tokenizer.c\
				parsing/tokinizer_2.c\

OBJ			=	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))

CC			=	gcc
CFLAGS		=	-g -Wall -Wextra -fsanitize=address #-static-libasan

FT			=	./libft/
FT_LIB		=	$(addprefix $(FT),libft.a)
FT_INC		=	-I ./libft

all:			obj $(FT_LIB) $(NAME)

obj:
				mkdir -p $(OBJDIR)
				mkdir -p $(LEXERDIR)
				mkdir -p $(PARSEDIR)
				mkdir -p $(GNLDIR)
				mkdir -p $(OTHERDIR)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c includes/minishell.h
				$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) -o $@ -c $< -lreadline

$(FT_LIB):
				make -C $(FT)

$(NAME):		$(OBJ)
				$(CC) $(CFLAGS) $(OBJ) $(FT_LIB) -lreadline -o $(NAME)

clean:
				rm -rf $(OBJDIR)
				make -C $(FT) clean

fclean:			clean
				rm -rf $(NAME)
				make -C $(FT) fclean

re: fclean all

