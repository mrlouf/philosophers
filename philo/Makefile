# -=-=-=-=-    NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

NAME		= 	philo

# -=-=-=-=-    PATH -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

# -=-=-=-=-    FILES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

SRC			=	philo.c		\
				utils.c

HEADER		=	philo.h

MAKE		=	Makefile

OBJDIR		= 	.obj

OBJS		= 	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

# -=-=-=-=-    FLAGS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

CC			=	-cc

CFLAGS		=	-Werror -Wextra -Wall -pthread -g -fsanitize=address

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