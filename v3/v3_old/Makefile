NAME := scop.out
CC := g++
CFLAGS := -Wall -Wextra -pedantic# -fsanitize=address

LIBS := -lX11 -lpthread -lm -lGL -lglfw -ldl
# -lX11 : 	Création de fenêtres et la gestion des événements graphiques.
# -lpthread:Programmation multithread
# -lm : 	Bibliothèque mathématique standard du C
# -lGL : 	Bibliothèque OpenGL pour le rendu graphique 2D et 3D 
# -lglfw : 	Création de fenêtres, contextes et surfaces OpenGL, ainsi que la gestion des entrées.
# -ldl : 	Chargement de bibliothèques partagées à l'exécution.

INCLUDES := -I./includes -I./lib

SRC_DIR := src
OBJ_DIR := obj

SRC_CPP := $(wildcard $(SRC_DIR)/*.cpp)
SRC_C 	:= $(wildcard $(SRC_DIR)/*.c)

OBJ_CPP := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_CPP))
OBJ_C 	:= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_C))

OBJ := $(OBJ_CPP) $(OBJ_C)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Building $(NAME)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBS) -o $(NAME)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $<"
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -O3 -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $<"
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -O3 -c $< -o $@

clean:
	@echo "Cleaning objs"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "Cleaning $(NAME)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
