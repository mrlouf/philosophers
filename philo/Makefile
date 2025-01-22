# -=-=-=-=-    NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

NAME		= 	philo

# -=-=-=-=-    PATH -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

# -=-=-=-=-    FILES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

SRC			=	main.c		\
				init.c		\
				routines.c	\
				checks.c	\
				utils.c		\
				prints.c

HEADER		=	philo.h

MAKE		=	Makefile

OBJDIR		= 	.obj

OBJS		= 	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

# -=-=-=-=-    FLAGS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

CC			=	-cc

# setarch `uname -m` -R $SHELL
CFLAGS		=	-Werror -Wextra -Wall -pthread -g# -fsanitize=thread# -fsanitize=address#

INCLUDE		=	-I.

# -=-=-=-=-    TARGETS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

all: $(NAME)

$(OBJDIR)/%.o: %.c $(HEADER) Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS) $(SRC)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(NAME)

clean:
	/bin/rm -fr $(OBJDIR)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY:  all clean fclean re