# g++ -x c++ first_program.cpp -x c glad.c -lglfw -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

# Compiler options
CC = gcc
CXX = g++
CFLAGS = -std=c++11

# Name of Binary Output file
OUTFILE = my_program

# makefile
THISFILE = makefile

# include directory (/usr/local/include)
IDIR = /Users/andreas/Documents/programming/OpenGL/glm/
CINCL = -I$(IDIR)

# folder for object files
ODIR = ./obj

# libraries
LDIR = /usr/local/lib
# or -lglfw3 for static library, 
CLIB = -lglfw

# MAC frameworks, -framework GLUT
CFRAME = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

# Object files
_OBJ = \
	hello_camera.o \
	libs/glad.o \
	libs/shader_input.o \
	libs/stb_image.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))	

# Dependencies
DEPS = \
	./libs/camera.h \
	./libs/shader_input.h	


program: folder_exists $(OBJ)
	$(CXX) $(CFLAGS) $(OBJ) -o $(OUTFILE) $(CLIB) $(CFRAME)

# ! shell command must be in one line, if test <=> if []
folder_exists:
	if [ ! -d "$(ODIR)" ]; then mkdir $(ODIR); fi
	if [ ! -d "$(ODIR)/libs" ]; then mkdir $(ODIR)/libs; fi

$(ODIR)/%.o: %.c 
	$(CC) -c -o $@ $<
	@echo "Compiling C-file"

$(ODIR)/%.o: %.cpp $(DEPS) $(THISFILE)
	$(CXX) -c -o $@ $< $(CFLAGS)
	@echo "Compiling C++ files"

$(ODIR)/libs/%.o: ./libs/%.cpp $(DEPS) $(THISFILE)
	$(CXX) -c -o $@ $< $(CFLAGS)
	@echo "Compiling C++ files"	

$(ODIR)/libs/%.o: ./libs/%.c 
	$(CC) -c -o $@ $<
	@echo "Compiling C-file"

clean:
	rm -f $(ODIR)/*.o *~ 	

