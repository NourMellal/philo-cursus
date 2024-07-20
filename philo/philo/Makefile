SRC = common.c freeing.c main.c parsing.c philo.c philo_utils.c routines.c
OBJ = $(SRC:.c=.o)
CC = cc
NAME = philo
CFLAGS = -Wall -Werror -Wextra -pthread

.PHONY : re fclean clean all

%.o : %.c
	$(CC) $(CFLAGS) $< -c -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all : $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all