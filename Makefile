NAME 	= cub3d
CC 		= cc
CFLAGS 	= -Wall -Werror -Wextra
INC 	= -I ./include

SRC =	./src/main.c \
		./src/cleanup.c \
		./src/map.c

OBJ = ${SRC:%.c=%.o}

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) ./tmp/libft.a $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re