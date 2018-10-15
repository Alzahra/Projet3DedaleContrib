SOURCES =	main.cpp \
		sdlglutils.cpp \
		trackballcamera.cpp
OBJECTS	=	$(SOURCES:.cpp=.o)
TARGET	=	sdlgl_08_trackball	
LIBS	=	$(shell sdl-config --libs) -lSDL_image -lGL -lGLU -L/usr/local/lib -lSDL2

all: $(OBJECTS)
	g++ $(LIBS) -o $(TARGET) $(OBJECTS)

%o: %cpp
	g++ -o $@ -c $<

x: all
	./$(TARGET)

clean:
	rm -rf $(OBJECTS)

superclean : clean
	rm -rf $(TARGET)

