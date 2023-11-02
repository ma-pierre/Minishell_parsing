NAME = minishell
SRCS = parse_main.c \
		parse_quotes.c \
		parse_syntax.c\
		parse_is_utils.c\
		parse_utils.c\
		parse_expand.c\
		parse_to_send.c\
		
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g
LIBS = -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

val:		$(NAME)
		valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --suppressions=rl_ignore --track-origins=yes ./${NAME}

re: fclean all

.PHONY: all clean fclean re
