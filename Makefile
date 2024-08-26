NAME = scop
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LIBS = -lmlx -lX11 -lXext -ldl -lglfw -pthread -lm
LIBS_OPENGL = -lGLEW -lGL -lglfw -lX11 -lpthread -lm
INCLUDES = -I./includes 
MLX = -Imlx_linux -Lmlx_linux

SRC_DIR = srcs
OBJ_DIR = obj
SRC = $(wildcard $(SRC_DIR)/*.c)

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBS) $(LIBS_OPENGL) $(MLX) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(MLX) -O3 -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

