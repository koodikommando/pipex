CC = cc -g
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
SOURCES = pipex.c \
			utils.c \
			child_processes.c \
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c \
			pipex_split.c
			
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) libft.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:  all clean fclean re