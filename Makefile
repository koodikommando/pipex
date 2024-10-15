CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
SOURCES = pipex.c \
			utils.c \
			child_processes.c \
			pipex_split.c
			
OBJECTS = $(SOURCES:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT)

$(LIBFT):
	make -C libft/

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	make clean -C libft/

fclean: clean
	rm -f $(NAME)
	make fclean -C libft/

re: fclean all

.PHONY:  all clean fclean re