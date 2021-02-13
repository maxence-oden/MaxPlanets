CC = g++
CFLAGS = -Wall -Wextra -lGL -lGLEW -lSDL2
CLIBS = `sdl2-config --cflags --libs` -lSDL2_image -lpthread

SRC =  src/display.cpp
SRC +=  src/shader.cpp
SRC +=  src/mesh.cpp
SRC +=  src/texture.cpp
SRC +=  src/obj_loader.cpp
SRC +=  src/planet.cpp
SRC +=  src/converts.cpp

all: ${SRC} ${SRC}
	${CC} main.cpp ${SRC} ${CLIBS} ${CFLAGS} -g -o main