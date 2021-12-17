SRCS	= srcs/pipex.c\
 					utils/utils.c utils/utils2.c utils/utils3.c
OBJS	= ${SRCS:.c=.o}
NAME	= pipex

SRCS_B	= srcs/pipex_bonus.c\
					utils/utils.c utils/utils2.c utils/utils3.c
OBJS_B	= ${SRCS_B:.c=.o}

HDRS	= -I./includes/pipex.h

CC		= gcc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror ${HDRS}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
				${CC} ${HEADER} ${OBJS} -o ${NAME}

all:		${NAME}

bonus:		${OBJS_B}
				${CC} ${HEADER} ${OBJS_B} -o ${NAME}

clean:
			${RM} ${OBJS} ${OBJS_B}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus
