NAME = scop
CC = g++
CFLAGS = -Wall -Wextra -g -fsanitize=address

LIB_GLEW = ./external/glew-2.1.0/lib/libGLEW.a

LIBS = -lX11 -lpthread -lm -lGL -lglfw
LIBS += $(LIB_GLEW)

INCLUDES = 	-I. \
			-I./external/glm-1.0.1 \
			-I./external/glfw-3.1.2/include  \
			-I./external/glew-2.1.0/include

SRC_DIR = .
COMMON_DIR = common
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.cpp)
SRC += $(wildcard $(COMMON_DIR)/*.cpp)

# Adjust object files list to account for different directories
OBJ =  $(patsubst $(SRC_DIR)/%.cpp,    $(OBJ_DIR)/%.o,        $(SRC))
OBJ := $(patsubst $(COMMON_DIR)/%.cpp, $(OBJ_DIR)/common/%.o, $(OBJ))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBS) -o $(NAME)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -O3 -c $< -o $@

$(OBJ_DIR)/$(COMMON_DIR)/%.o: $(COMMON_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)/common
	$(CC) $(CFLAGS) $(INCLUDES) -O3 -c $< -o $@


clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
