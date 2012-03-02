ROOTCFLAGS := $(shell root-config --cflags)
ROOTLIBS := $(shell root-config --glibs)  -lMinuit -lHtml -lThread
CXX         = g++  ${ROOTCFLAGS}
CXXFLAGS    = -g -Wall

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
EXE = main

all : $(EXE)

$(EXE):$(OBJ)
	$(CXX) ${ROOTLIBS} -o $(EXE) $(OBJ)

%.o : %.cpp
	@echo "-> Building object : " $@
	@$(CXX) $(CXXFLAGS) -fPIC  -o $@  -c $<

clean :
	@rm -f *.o

