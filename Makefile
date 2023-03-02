NAME 	= cub3d
CC 		= cc
CFLAGS 	= -Wall -Werror -Wextra
INC 	= -I ./include
LFLAGS = -framework Cocoa -framework OpenGL -framework IOKit

SRC =	./src/main.c \
		./src/cleanup.c \
		./src/map_parsing.c \
		./src/map_validating.c \
		./src/error.c \
		./src/utility_array.c \
		./src/utility_map.c

OBJ = ${SRC:%.c=%.o}

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) ./tmp/libft.a ./tmp/libmlx42.a $(OBJ) -lglfw3 $(LFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re