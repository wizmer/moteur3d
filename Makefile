CXXFLAGS    := -g -Wall
LIBS :=  -L/usr/X11/lib -lX11
CXX       = g++
OPENMP := -fopenmp

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
EXE = main

all : $(EXE)

$(EXE):$(OBJ)
	$(CXX) ${LIBS} ${OPENMP} -o $(EXE) $(OBJ)

%.o : %.cpp
	@echo "-> Building object : " $@
	@$(CXX) $(CXXFLAGS) ${OPENMP} -fPIC  -o $@  -c $<

clean :
	@rm -f *.o
	@rm -f main

