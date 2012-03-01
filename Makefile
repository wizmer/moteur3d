# ROOTCFLAGS := $(shell root-config --cflags)
# ROOTLIBS := $(shell root-config --glibs)  -lMinuit -lHtml -lThread
SOFLAGS       =  -dynamiclib -single_module -undefined dynamic_lookup

all:
	g++ -c Point.cpp -o libPoint.o
	g++ -c Surface.cpp -o libSurface.o
	g++ -c ${ROOTCFLAGS}  Object.cpp -o libObject.o 
	g++ -c ${ROOTCFLAGS}  WorldObject.cpp -o libWObject.o 
	g++ -c ${ROOTCFLAGS}  WorldManager.cpp -o libWManager.o 
	g++ ${SOFLAGS}  -o libObj.so libPoint.o libSurface.o libObject.o libWObject.o libWManager.o
	g++ ${ROOTCFLAGS} -L/Users/coste/Desktop/moteur -lObj ${ROOTLIBS}  go.cpp -o go

clean:
	rm -f *.so *.o go