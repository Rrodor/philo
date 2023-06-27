NAME= philo
SRC= philo.c philo_threads.c philo_utils.c
SRCPATH= ./cfiles/
OBJ= $(SRC:.c=.o)
OBJS= $(addprefix $(OBJPATH), $(OBJ))
SRCS= $(addprefix $(SRCPATH), $(SRC))
OBJPATH= ./ofiles/

CC= gcc -Wall -Wextra -Werror -lpthread -D_REENTRANT

all: $(NAME)

$(OBJPATH)%.o: $(SRCPATH)%.c
	mkdir -p ofiles
	$(CC) -I./hfiles -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -I./hfiles

clean:
	rm -f $(OBJS)
	rm -rf ofiles

fclean: clean
	rm -f $(NAME)

re: fclean all
