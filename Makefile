NAME=		philo

VPATH=		src/

OBJDIR=		obj

INCDIR=		inc

SRC=		main.c			\
			parsing.c		\
			utils1.c		\
			utils2.c		\
			init_data.c		\
			time.c			\
			routine.c


OBJ=		${addprefix ${OBJDIR}/,		\
			${SRC:.c=.o}}

INC=		${INCDIR}

CC=			cc

CFLAGS=		-Wall -Wextra 

all:		${OBJDIR} ${NAME}

${NAME}:	${OBJ} ${INC}
			${CC} ${OBJ} -o ${NAME}

${OBJDIR}:
			mkdir -p obj

${OBJDIR}/%.o:	%.c ${INC} Makefile 
			${CC} ${CFLAGS} -c $< -o $@


clean:
			rm -rf ${OBJDIR}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re