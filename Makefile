CC = g++
CFLAGS = $(patsubst %, -I%, $(INCLUDES)) -std=c++11
INCLUDES = include include/opengl
SRC_DIR = src
LIB_DIR = lib
OBJ_DIR = $(SRC_DIR)/obj
BIN_DIR = bin
OPENGL_FILES = $(wildcard $(SRC_DIR)/opengl/*.cpp)
CPP_FILES = $(wildcard $(SRC_DIR)/*.cpp)

GRAPHIC_LIBS = OpenGL GLUT
BULLET_LIBS = LinearMath BulletCollision BulletDynamics

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(CPP_FILES:.cpp=.o)))
OPENGL_OBJ = $(addprefix $(OBJ_DIR)/opengl/, $(notdir $(OPENGL_FILES:.cpp=.o)))

_FRAMEWORKS = $(GRAPHIC_LIBS) $(BULLET_LIBS)
FRAMEWORKS = $(patsubst %, -framework %, $(_FRAMEWORKS))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR)/opengl/%.o: $(SRC_DIR)/opengl/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

walker.out: $(OBJ) $(OPENGL_OBJ)
	$(CC) $(FRAMEWORKS) -o $(BIN_DIR)/$@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ_DIR)/*.o $(OBJ_DIR)/opengl/*.o $(BIN_DIR)/*
