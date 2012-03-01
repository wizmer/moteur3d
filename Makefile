CXX         = g++
CXXFLAGS    = -g -Wall

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
EXE = main

all : $(EXE)

$(EXE):$(OBJ)
	$(CXX) -o $(EXE) $(OBJ)

%.o : %.cpp
	@echo "-> Building object : " $@
	@$(CXX) $(CXXFLAGS) -fPIC  -o $@  -c $<

clean :
	@rm -f *.o

