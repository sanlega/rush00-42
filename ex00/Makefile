NAME		= rush01
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
SRCS		= main.c parse.c board.c ft_split.c utils.c logic.c visible.c \
			  check.c solve.c
OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
