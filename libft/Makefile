SRCS		= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_tolower.c ft_toupper.c \
			  ft_strlen.c ft_strchr.c ft_strrchr.c ft_strcat.c ft_strupper.c ft_strlower.c\
			  ft_isprint.c ft_strlen.c ft_atoi.c ft_memset.c ft_memchr.c ft_memcmp.c\
			  ft_bzero.c ft_memmove.c ft_memcpy.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c ft_strncmp.c ft_strcmp.c\
			  ft_substr.c ft_strdup.c ft_calloc.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_split.c \
			  ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			  ft_straddc.c\

SRCS_BONUS	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
			  ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_lstdel.c\

OBJS		= ${SRCS:.c=.o}

OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

NAME		= libft.a

CC			= cc

CFLAGS		= -Wall -Wextra -Werror

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

RM			= rm -f

${NAME}:	${OBJS} ${OBJS_BONUS}
			ar rcs ${NAME} ${OBJS} ${OBJS_BONUS}

all:        ${NAME}

bonus:		${OBJS_BONUS}
			ar rcs ${NAME} ${OBJS_BONUS}

clean:
			${RM} ${OBJS} ${OBJS_BONUS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all bonus clean fclean re
