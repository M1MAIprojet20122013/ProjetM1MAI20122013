CC = gcc
CXX = g++
LINKER = g++
GOB = gob2

CFLAGS = 
CXXFLAGS = -std=c++11 
MAINFLAGS = -Wall -Werror -g -pg -fprofile-arcs -ftest-coverage -fno-inline -DDEBUG

LIBDIR = 
LIB = -lgcov

INCLUDEDIR = 

TARGET = msh_reader

OBJECTS = main.o Point.o Mesh.o Domain.o plot.o commun.o solver.o Matrice.o BoundaryManager.o

all: $(OBJECTS)
	$(LINKER) $(LIBDIR) $(OBJECTS) -o $(TARGET) $(LIB)
.c.o:
	$(CC) $(INCLUDEDIR) $(MAINFLAGS) $(CFLAGS) -c $< -o $@ 
.cpp.o:
	$(CXX) $(INCLUDEDIR) $(MAINFLAGS) $(CXXFLAGS)  -c $< -o $@
%.o : %.gob
	$(GOB) $< 
	$(CC) $(INCLUDEDIR) $(MAINFLAGS) $(CFLAGS) -c $*.c -o $*.o
	rm $*.c  
clean:
	rm *.o
clean-all: 
	rm *.o $(TARGET) *.gcno *.gcda
