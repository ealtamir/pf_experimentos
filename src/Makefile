CC = gcc
CFLAGS = -I$(INCLUDES)
INCLUDES = ../include
LIB_DIR = ../lib
OBJ_DIR = obj
BIN_DIR = ../bin

GRAPHIC_LIBS = OpenGL GLUT
BULLET_LIBS = LinearMath BulletCollision BulletDynamics


_DEPS = printing.h
DEPS = $(patsubst %, $(INCLUDES)/%, $(_DEPS))

_OBJ = printing.o main.o
OBJ = $(patsubst %, $(OBJ_DIR)/%, $(_OBJ))

_FRAMEWORKS = $(GRAPHIC_LIBS) $(BULLET_LIBS)
FRAMEWORKS = $(patsubst %, -framework %, $(_FRAMEWORKS))

$(OBJ_DIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

printer: $(OBJ)
	gcc $(FRAMEWORKS) -o $(BIN_DIR)/$@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ_DIR)/*.o
