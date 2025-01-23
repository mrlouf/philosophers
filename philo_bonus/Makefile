# -=-=-=-=-    NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

NAME		= 	philo_bonus

# -=-=-=-=-    PATH -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

# -=-=-=-=-    FILES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

SRC			=	main_bonus.c		\
				prints_bonus.c		\
				checks_bonus.c		\
				init_bonus.c		\
				routines_bonus.c	\
				utils1_bonus.c		\
				utils2_bonus.c

HEADER		=	philo_bonus.h

MAKE		=	Makefile

OBJDIR		= 	.obj

OBJS		= 	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

# -=-=-=-=-    FLAGS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

CC			=	-cc

CFLAGS		=	-Werror -Wextra -Wall -pthread -g# -fsanitize=thread#-fsanitize=address

INCLUDE		=	-I.

# -=-=-=-=-    TARGETS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

bonus: $(NAME)

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