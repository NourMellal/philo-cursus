SRC = common_bonus.c freeing_bonus.c main_bonus.c monitor_bonus.c parsing_bonus.c philo_bonus.c philo_utils_bonus.c routine_bonus.c
OBJ = $(SRC:.c=.o)
CC = cc
NAME = philo_bonus
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