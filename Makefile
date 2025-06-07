NAME = RayLibGame 
SRC_DIR = src
SRC_FILES = main.cpp PlayerInput.cpp Game.cpp Movement.cpp Render3D.cpp RenderUI.cpp AssetsManager.cpp Collision.cpp
HEADER_DIR = include
OBJ_DIR = obj

SRC = $(addprefix	$(SRC_DIR)/, $(SRC_FILES))
OBJ = $(subst $(SRC_DIR),$(OBJ_DIR), $(SRC:.cpp=.o))
INCLUDES = -I$(HEADER_DIR)
FLAGS = -std=c++17 -O3 -fsanitize=address
COMPILER = g++ 

MAC_LINKING = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -Llib -lraylib 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(COMPILER) $(FLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[96mcompiling \033[0;33m"$(NAME)"\033[0m"
	@$(COMPILER) $(FLAGS) $(INCLUDES) $(MAC_LINKING) $(OBJ) -o $(NAME)

clean:
	@echo "\033[0;31mremoving files: \033[0m" $(OBJ)
	@rm -rf $(OBJ)

fclean: clean
	@echo "\033[0;31mremoving file: \033[0m" $(NAME)
	@rm -rf $(NAME)

re: fclean all

.PHONY = all clean fclean re
