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
all: main_reduce

main_reduce: main_reduce.o reduce.o reduce_Dict.o 
	$(CC) main_reduce.o reduce.o reduce_Dict.o $(ROOTLIBS) -o main_reduce 

main_reduce.o: main_reduce.cpp
	$(CC) -c main_reduce.cpp 

reduce.o: reduce.cpp reduce.h
	$(CC) -c reduce.cpp -o reduce.o 

reduce_Dict.cxx: reduce.h
	rootcint -f reduce_Dict.cxx -c reduce.h

reduce_Dict.o: reduce_Dict.cxx
	$(CC) -c reduce_Dict.cxx -o reduce_Dict.o

### clean up
clean:
	rm -rf *.o
	rm -rf *.so
	rm -rf *~
	rm -rf }*.o
	rm -rf *_Dict*
	rm -rf main_reduce
clean1:
	rm -rf *.o
	rm -rf *.so
	rm -rf *~
	rm -rf *_Dict*
	rm -rf *.o
