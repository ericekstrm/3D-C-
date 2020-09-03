CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g -fsanitize=address
LDFLAGS =  -fsanitize=address

SRC = Camera.cc Game.cc GUIText.cc Loader.cc main.cc Matrix.cc MenuState.cc Model.cc RunState.cc Shader.cc Skybox.cc stb_image.cc Terrain.cc Vector.cc
OBJ = $(SRC:.cc=.o)
EXEC = main.cc

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)