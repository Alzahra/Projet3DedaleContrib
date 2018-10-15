UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	FLAGS = -lGL -lGLU -lglut
endif

ifeq ($(UNAME_S),Darwin)
	FLAGS = -framework OpenGL -framework glut
endif

all: main

main: main.o 
	$(CXX) -o $@ main.o $(FLAGS) 

main.o: main.c 
	$(CXX) -c main.c $(FLAGS) 

clean:
	rm *.o main