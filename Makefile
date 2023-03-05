# tool macros
CC			:= cc
CFLAGS		:= -Wall -Werror -Wextra
COBJFLAGS	:= $(CFLAGS) $(LFLAGS)

# path macros
HEADERS		:= -I libs/libft/include -I libs/MLX42/include/MLX42
HDR_PATH	:= -I include
BIN_PATH	:= bin
OBJ_PATH	:= obj
SRC_PATH	:= src
LIBFT		:= libs/libft/libft.a
MLX			:= libs/MLX42/build/libmlx42.a

# detect OS for LFLAGS
OS			:= $(shell uname)
ifeq ($(OS),Linux)
		LFLAGS := -ldl -lglfw -pthread -lm
else
		LFLAGS := -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
endif

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
					utility_map \
					hooks_main \
					hooks_strafe \
					hooks_camera \
					location_validating))
OBJ 		:= $(subst src, obj, $(SRC:.c=.o))

default: mkdir all
	@git submodule update --init --recursive

$(TARGET): $(OBJ)
	@$(CC) $(OBJ) $(CFLAGS) $(LIBFT) $(MLX) $(HDR_PATH) $(HEADERS) $(LFLAGS) -o $(TARGET)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HDR_PATH)

all: $(TARGET)

run: default
	@./$(TARGET) assets/maps/$(MAP).cub

submodule:
	@git submodule update --init --recursive
	@git submodule update --remote --merge
	@$(MAKE) -C libs/libft

mkdir:
	@mkdir -p $(BIN_PATH) $(OBJ_PATH)

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -rf $(BIN_PATH)

re: fclean default

.PHONY: all clean fclean re run default mkdir submodule_update

# # tool macros
# CC			:= cc
# CFLAGS		:= -Wall -Werror -Wextra
# COBJFLAGS	:= $(CFLAGS) $(LFLAGS)

# # path macros
# LIBFT_H		:= -I libs/libft/include
# MLX_H		:= -I libs/MLX42/include/MLX42
# HDR_PATH	:= -I include
# BIN_PATH	:= bin
# OBJ_PATH	:= obj
# SRC_PATH	:= src
# LIBFT		:= libs/libft/libft.a
# MLX			:= libs/MLX42/build/libmlx42.a
# OS			:= $(shell uname)

# ifeq ($(OS),Linux)
# 		GLFW := -ldl -lglfw -g -pthread -lm
# else
# 		GLFW := -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
# endif


# # compile macros
# TARGET_NAME := cub3d
# TARGET		:= $(BIN_PATH)/$(TARGET_NAME)

# # color macros
# GREEN		:= \033[1;32m
# RED			:= \033[1;31m
# BLUE		:= \033[1;34m
# MAGENTA		:= \033[1;35m
# RESET		:= \033[0m

# # source- & object files
# SRC			:= $(addprefix src/, $(addsuffix .c, \
# 					main \
# 					cleanup \
# 					map_parsing \
# 					map_validating \
# 					error \
# 					textures \
# 					graphics_setup \
# 					utility_array \
# 					utility_map))
# OBJ 		:= $(subst src, obj, $(SRC:.c=.o))

# default: mkdir all

# $(TARGET): $(OBJ)
# 	@$(CC) $(CFLAGS) -ldl -lglfw -g -pthread -lm libs/MLX42/build/libmlx42.a -o $@ $(OBJ) -o $(TARGET)

# $(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
# 	@$(CC) $(CFLAGS) -c -o $@ $< $(HDR_PATH)

# all: $(TARGET)

# run: default
# 	@./$(TARGET) assets/maps/$(MAP).cub

# submodule:
# 	@git submodule update --init --recursive
# 	@git submodule update --remote --merge
# 	@$(MAKE) -C libs/libft
# 	cmake -B build
# 	@cmake --build build -j4

# mkdir:
# 	@mkdir -p $(BIN_PATH) $(OBJ_PATH)

# clean:
# 	@rm -rf $(OBJ_PATH)

# fclean: clean
# 	@rm -rf $(BIN_PATH)

# re: fclean default

# .PHONY: all clean fclean re run default mkdir submodule_update