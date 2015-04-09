CXXFLAGS    := -g -Wall
LIBS :=  -L/usr/X11/lib -lX11 -lopencv_core -lopencv_imgproc -lopencv_calib3d -lopencv_video -lopencv_features2d -lopencv_ml -lopencv_highgui -lopencv_objdetect -lopencv_contrib -lopencv_legacy
CXX       = g++
OPENMP := -fopenmp

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
EXE = main

all : $(EXE)

$(EXE):$(OBJ)
	@echo "-> Building exe : " $@
	@$(CXX) ${LIBS} ${OPENMP} -o $(EXE) $(OBJ)

%.o : %.cpp
	@echo "-> Building object : " $@
	@$(CXX) $(CXXFLAGS) ${OPENMP} ${INC} -fPIC  -o $@  -c $<

clean :
	@rm -f *.o
	@rm -f main

