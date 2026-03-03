NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror


SRCS = main.c utils.c routine.c init.c monitor.c philo_one.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean: 
	rm -rf $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re