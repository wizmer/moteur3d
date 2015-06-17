CXXFLAGS    := -g -Wall -Wfatal-errors
LIBS :=  -lopencv_core -lopencv_imgproc -lopencv_calib3d -lopencv_video -lopencv_features2d -lopencv_ml -lopencv_highgui -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lX11
CXX       = g++
OPENMP := -fopenmp

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
EXE = main

all : $(EXE)

$(EXE):$(OBJ)
	@echo "-> Building exe : " $@
	@echo $(CXX)  -o $(EXE) $(OBJ)  -lGL -lglut  ${LIBS} ${OPENMP}
	@$(CXX)  -o $(EXE) $(OBJ)  -lGL -lglut  ${LIBS} ${OPENMP}

%.o : %.cpp
	@echo "-> Building object : " $@
	@echo $(CXX) $(CXXFLAGS) ${OPENMP} ${INC} -fPIC  -o $@  -c $<
	@$(CXX) $(CXXFLAGS) ${OPENMP} ${INC} -fPIC  -o $@  -c $<

clean :
	@rm -f *.o
	@rm -f main

