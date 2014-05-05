CC = gcc

PATH_SRC = src
PATH_OBJ = obj
PATH_DOC = doc
PATH_LIB = lib
PATH_BIN = bin
PATH_TESTS = tests
PATH_INCLUDE = include

FLAGS_CC_DEBUG = -Wall -g
FLAGS_INCLUDE = -I$(PATH_INCLUDE) -I/usr/X11R6/include -IGL
FLAGS_CC = $(FLAGS_INCLUDE) -std=c99 -pedantic -O0  $(FLAGS_CC_DEBUG)
FLAGS_LIB = -L/usr/X11R6/lib -L$(PATH_LIB) -lglut -lGL -lGLU -lm -lperlimpinpin

vpath %.h $(PATH_INCLUDE) $(PATH_TESTS)/include
vpath %.c $(PATH_SRC) $(PATH_SRC)/src
vpath %.o $(PATH_OBJ)
vpath %.a $(PATH_LIB)

all : main

%.o: %.c | obj_dir
		$(CC) $(FLAGS_CC) -o $(PATH_OBJ)/$@ -c $<

main: main.o libperlimpinpin.a | bin_dir
		$(CC) -o $(PATH_BIN)/$@ $(PATH_OBJ)/main.o $(FLAGS_LIB)

main.o: main.c vector.h polygon.h mesh.h
vector.o: vector.c vector.h
polygon.o: polygon.c polygon.h vector.h
perlin.o: perlin.c perlin.h vector.h
mesh.o: mesh.c mesh.h vector.h polygon.h perlin.h

libperlimpinpin.a: vector.o polygon.o perlin.o mesh.o | lib_dir
		ar -crv $(PATH_LIB)/libperlimpinpin.a $(PATH_OBJ)/vector.o $(PATH_OBJ)/polygon.o $(PATH_OBJ)/perlin.o $(PATH_OBJ)/mesh.o
		ranlib $(PATH_LIB)/libperlimpinpin.a

tests: main
	@echo "TODO."

obj_dir:
		@mkdir -p $(PATH_OBJ)

lib_dir:
		@mkdir -p $(PATH_LIB)

bin_dir:
		@mkdir -p $(PATH_BIN)

clean:
		rm -rf $(PATH_BIN) $(PATH_OBJ) $(PATH_LIB)

cleanall: clean
		@echo "Clean."
