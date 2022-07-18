# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aptive <aptive@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/30 20:18:17 by tdelauna          #+#    #+#              #
#    Updated: 2022/07/18 19:30:46 by aptive           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    	=	minishell

SRCDIR		=	./src
INCDIR		=	./includes
OBJDIR		=	obj
EXPANDDIR	=	obj/expand
PARSEDIR	=	obj/parsing

SRC			=	main.c\
				get_next_line.c\
				get_next_line_utils.c\
				env.c\
				redirection.c\
				affichage.c\
				command.c\
				parsing.c\
				builtin.c\
				echo.c\
				lst_management.c\
				change_dir.c\
				utils.c\
				exec.c\
				heredoc.c\
				exporter.c\
				errors.c\
				redir.c\
				tokenizer.c\
				tokinizer_2.c\
				free.c\
				signal.c\
				split_pipe.c\
				verif_line.c\
				exiting.c\
				parse_quote.c\
				parse_back.c\
				expand/expand.c\
				expand/expand_utils.c\


OBJ			=	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))

CC			=	gcc
CFLAGS		=	-g -Wall -Wextra -fsanitize=address #-static-libasan

FT			=	./libft/
FT_LIB		=	$(addprefix $(FT),libft.a)
FT_INC		=	-I ./libft

all:			obj $(FT_LIB) $(NAME)

obj:
				mkdir -p $(OBJDIR)
				mkdir -p $(EXPANDDIR)
				mkdir -p $(PARSEDIR)

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

