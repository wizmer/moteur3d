CXXFLAGS    := -g -Wall
LIBS :=  -L/usr/X11/lib -lX11 -L//Users/coste/appz/OpenCV/opencv/release/lib  -lopencv_core -lopencv_imgproc -lopencv_calib3d -lopencv_video -lopencv_features2d -lopencv_ml -lopencv_highgui -lopencv_objdetect -lopencv_contrib -lopencv_legacy
INC  := -I//Users/coste/appz/OpenCV/opencv/modules/core/include -I//Users/coste/appz/OpenCV/opencv/modules/highgui/include -I//Users/coste/appz/OpenCV/opencv/modules/imgproc/include/ -I//Users/coste/appz/OpenCV/opencv/modules/video/include/ -I//Users/coste/appz/OpenCV/opencv/modules/features2d/include/ -I//Users/coste/appz/OpenCV/opencv/modules/flann/include/ -I//Users/coste/appz/OpenCV/opencv/modules/calib3d/include/ -I//Users/coste/appz/OpenCV/opencv/modules/objdetect/include/ -I//Users/coste/appz/OpenCV/opencv/modules/legacy/include/ -I/Users/coste/appz/OpenCV/opencv/include/opencv 
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

