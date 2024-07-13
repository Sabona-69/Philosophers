NAME	= philo

RM		= rm -f

SRC		= philo.c utils.c \

CFLAGS	=  -g -fsanitize=address #-Wall -Wextra -Werror

OBJ		= $(SRC:.c=.o)

CC		= cc

all		: $(NAME) clean
			
%.o		: %.c philo.h
			cc $(CFLAGS) -c $<  -o $@
$(NAME)	: $(OBJ) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJ) -o $@
clean	: 
			$(RM) $(OBJ)

fclean	: clean
			$(RM) $(NAME)

re		: fclean all

