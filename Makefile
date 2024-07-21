SRC = cleaner.c monitoring.c philo.c philo_utils2.c routines.c\
main.c parsing.c philo_utils.c

OBJS = $(SRC:.c=.o)
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g3
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJS)