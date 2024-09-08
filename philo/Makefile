NAME	= philo

RM		= rm -f

SRC		= philo.c utils.c actions.c \

CFLAGS	= -pthread#-fsanitize=thread -g3 #  -pthread #-Wall -Wextra -Werror

OBJ		= $(SRC:.c=.o)

CC		= cc

all		: $(NAME)
			
%.o		: %.c philo.h Makefile
			cc $(CFLAGS) -c $<  -o $@
$(NAME)	: $(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $@
clean	: 
			$(RM) $(OBJ)

fclean	: clean
			$(RM) $(NAME)

re		: fclean all

