CC	= gcc
CFLAGS	= -Wall -Wextra -Werror
NAME	= philo

SRCS_DIR = srcs
OBJS_DIR = objs
INCLUDE_DIR = include
SRCS = main.c utils.c parser.c
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c $(INCLUDE_DIR)/philo.h
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c -o $@ $<

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
