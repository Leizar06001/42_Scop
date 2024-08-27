NAME = scop
CC = g++
CFLAGS = -Wall -Wextra -g
LIBS = -lmlx -lX11 -lXext -ldl -lglfw -pthread -lm
LIBS_OPENGL = -lGLEW -lGL -lglfw -lX11 -lpthread -lm
INCLUDES = -I./includes

SRC_DIR = src
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.cpp)
SRCC = $(wildcard $(SRC_DIR)/*.c)

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.cpp=.o)))

OBJC = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCC:.c=.o)))

all: $(NAME)

$(NAME): $(OBJ) $(OBJC)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(OBJC) $(LIBS_OPENGL) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -O3 -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -O3 -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
