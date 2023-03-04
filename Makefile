# tool macros
CC			:= cc
CFLAGS		:= -Wall -Werror -Wextra
LFLAGS		:= -framework Cocoa -framework OpenGL -framework IOKit
COBJFLAGS	:= $(CFLAGS) $(LFLAGS)

# path macros
LIBFT_H		:= libs/libft/include
# MLX_H		:= libs/MLX42/
HDR_PATH	:= -I include
BIN_PATH	:= bin
OBJ_PATH	:= obj
SRC_PATH	:= src
LIBFT		:= libs/libft/libft.a
MLX			:= libs/MLX42/build/libmlx42.a


# compile macros
TARGET_NAME := cub3d
TARGET		:= $(BIN_PATH)/$(TARGET_NAME)

# color macros
GREEN		:= \033[1;32m
RED			:= \033[1;31m
BLUE		:= \033[1;34m
MAGENTA		:= \033[1;35m
RESET		:= \033[0m

# source- & object files
SRC			:= $(addprefix src/, $(addsuffix .c, \
					main \
					cleanup \
					map_parsing \
					map_validating \
					error \
					textures \
					graphics_setup \
					utility_array \
					utility_map))
OBJ 		:= $(subst src, obj, $(SRC:.c=.o))

default: mkdir all
	@git submodule update --init --recursive

$(TARGET): $(OBJ)
	@$(CC) $(CFLAGS) $(LIBFT) $(MLX) -o $@ $(OBJ) -lglfw3 $(LFLAGS) -o $(TARGET)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $< $(HDR_PATH)

all: $(TARGET)

run: default
	@./$(TARGET) assets/maps/$(MAP).cub

submodule_update:
	@git submodule update --remote --merge

mkdir:
	@mkdir -p $(BIN_PATH) $(OBJ_PATH)

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -rf $(BIN_PATH)

re: fclean default

.PHONY: all clean fclean re run default mkdir submodule_update