NAME    	= minishell

SRCDIR			= ./srcs
INCDIR			= ./includes
OBJDIR			= obj

SRC				= 	


OBJ				= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

CC				= clang
CFLAGS			= -Wall -Wextra -Werror -g

FT			=	./libft/
FT_LIB		=	$(addprefix $(FT),libft.a)
FT_INC		=	-I ./libft

all:			obj $(FT_LIB) $(NAME)

obj:
				mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c
				$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
				make -C $(FT)

$(NAME):		$(OBJ)
				$(CC) $(CFLAGS) $(OBJ) $(FT_LIB) -o $(NAME)

clean:
				rm -rf $(OBJDIR)
				make -C $(FT) clean

fclean:			clean
				rm -rf $(NAME)
				make -C $(FT) fclean

re: fclean all

