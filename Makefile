CC = gcc

PATH_SRC = src
PATH_OBJ = obj
PATH_DOC = doc
PATH_LIB = lib
PATH_BIN = bin
PATH_TESTS = tests
PATH_INCLUDE = include

FLAGS_CC_DEBUG = -Wall -g -D__ENABLE_DEBUG
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
utilities.o: utilities.c utilities.h
vector.o: vector.c vector.h utilities.h
polygon.o: polygon.c polygon.h vector.h
perlin.o: perlin.c perlin.h vector.h
quad.o: quad.c quad.h vector.h
mesh.o: mesh.c mesh.h vector.h polygon.h perlin.h quad.h
window_common.o: window_common.c window_common.h utilities.h vector.h polygon.h mesh.h
window.o: window.c window.h utilities.h vector.h polygon.h mesh.h perlin.h window_callback.h
window_callback.o: window_callback.c window_callback.h window_common.h utilities.h vector.h polygon.h mesh.h perlin.h

libperlimpinpin.a: utilities.o vector.o polygon.o perlin.o quad.o mesh.o window_common.o window_callback.o window.o | lib_dir
		ar -crv $(PATH_LIB)/libperlimpinpin.a $(PATH_OBJ)/utilities.o $(PATH_OBJ)/vector.o $(PATH_OBJ)/polygon.o $(PATH_OBJ)/perlin.o $(PATH_OBJ)/quad.o $(PATH_OBJ)/mesh.o $(PATH_OBJ)/window_common.o $(PATH_OBJ)/window_callback.o $(PATH_OBJ)/window.o
		ranlib $(PATH_LIB)/libperlimpinpin.a

tests: main
		@echo "TODO."

doc: clean_doc
		@doxygen

obj_dir:
		@mkdir -p $(PATH_OBJ)

lib_dir:
		@mkdir -p $(PATH_LIB)

bin_dir:
		@mkdir -p $(PATH_BIN)

clean:
		@rm -rf $(PATH_BIN) $(PATH_OBJ) $(PATH_LIB)
		@echo "Clean."

cleandoc: clean_doc
clean_doc:
		@rm -rf $(PATH_DOC)

cleanall: clean_all
clean_all: clean clean_doc
		@echo "Super clean."
