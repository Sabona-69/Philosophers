NAME	= philo_bonus

RM		= rm -f

SRC		= philo_bonus.c utils_bonus.c actions_bonus.c \

CFLAGS	= -Wall -Wextra -Werror


OBJ		= $(SRC:.c=.o)

CC		= cc

all		: $(NAME)
			
%.o		: %.c philo_bonus.h
			cc $(CFLAGS) -c $<  -o $@
$(NAME)	: $(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $@
clean	: 
			$(RM) $(OBJ)

fclean	: clean
			$(RM) $(NAME)

re		: fclean all

