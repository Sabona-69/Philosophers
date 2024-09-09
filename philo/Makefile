NAME	= philo

RM		= rm -f

SRC		= philo.c utils.c actions.c \

CFLAGS	= -Wall -Wextra -Werror #-fsanitize=thread -g3 

OBJ		= $(SRC:.c=.o)

CC		= cc

all		: $(NAME)
			
%.o		: %.c philo.h
			cc $(CFLAGS) -c $<  -o $@
$(NAME)	: $(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $@
clean	: 
			$(RM) $(OBJ)

fclean	: clean
			$(RM) $(NAME)

re		: fclean all

