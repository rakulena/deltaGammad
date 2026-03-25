### ROOT setting
ROOTLIBS = `root-config --libs` -lRooFit -lHtml -lThread -lMinuit -lRooFitCore -lMathCore -lRooStats -lMathMore 
OPTCOMP = `root-config --cflags` 

### FLAGS
SPECIALFLAGS= --exceptions
LFLAGS =
RCXX = $(ROOTCFLAGS)
DBG = -g -L -O -w 

CC = g++ ${DBG} $(RCXX) $(OPTCOMP)

path = ../../inc/

### targets
all: main_massfit

LinkSrc=  main_massfit.o massfit.o massfit_Dict.o RooIpatia2.o RooIpatia2_Dict.o 

main_massfit: $(LinkSrc)
	$(CC) $(LinkSrc) $(ROOTLIBS) -o main_massfit

#main_massfit.o: ${path}main_massfit.cpp
#	$(CC) -c ${path}main_massfit.cpp 

main_massfit.o: main_massfit.cpp
	$(CC) -c main_massfit.cpp 

massfit.o: massfit.cpp massfit.h
	$(CC) -c massfit.cpp -o massfit.o 

massfit_Dict.cxx: massfit.h
	rootcint -f massfit_Dict.cxx -c massfit.h

massfit_Dict.o: massfit_Dict.cxx
	$(CC) -c massfit_Dict.cxx -o massfit_Dict.o

RooIpatia2.o: ${path}RooIpatia2.cxx ${path}RooIpatia2.h
	$(CC) -c ${path}RooIpatia2.cxx -o RooIpatia2.o

RooIpatia2_Dict.cxx: ${path}RooIpatia2.h
	rootcint -f RooIpatia2_Dict.cxx -c ${path}RooIpatia2.h

RooIpatia2_Dict.o: RooIpatia2_Dict.cxx
	$(CC) -c RooIpatia2_Dict.cxx -o RooIpatia2_Dict.o



### clean up
clean:
	rm -rf *.o
	rm -rf *.so
	rm -rf *~
	rm -rf *.o
	rm -rf *_Dict*
	rm -rf main_massfit
clean1:
	rm -rf *.o
	rm -rf *.so
	rm -rf *~
	rm -rf *_Dict*
	rm -rf *.o

