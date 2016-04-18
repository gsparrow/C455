CXX=g++
LINKER=$(CXX)

CFLAGS=-o3 -std=c++11

SRCC=main.cpp
OBJ=main.o
EXEC=the_program.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(LINKER) -o $(EXEC) $(OBJ)

%.o:%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(EXEC) *.o
