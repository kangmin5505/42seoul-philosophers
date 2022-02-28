CC	= gcc
CFLAGS	= -Wall -Wextra -Werror
NAME	= philo_bonus

SRCS =
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.c philo.h
	$(CC) $(CFAGS) -c $<

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
