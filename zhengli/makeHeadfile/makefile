### ROOT setting
ROOTLIBS = `root-config --libs` -lMinuit -lRooStats -lRooFit 
OPTCOMP = `root-config --cflags`

### FLAGS
SPECIALFLAGS= --exceptions
LFLAGS =
RCXX = $(ROOTCFLAGS)
DBG = -g -L -O -w 

CC = g++ ${DBG} $(RCXX) $(OPTCOMP)

### targets
all: MakeHeadfile

### makeselector
MakeHeadfile: MakeHeadfile.o
	$(CC) MakeHeadfile.o $(ROOTLIBS) -o MakeHeadfile

MakeHeadfile.o: MakeHeadfile.cpp
	$(CC) -c MakeHeadfile.cpp

### clean up
clean:
	rm -rf *.o
	rm -rf *~
	rm -rf *_Dict*
	rm -rf MakeHeadfile
clean1:
	rm -rf *.o
	rm -rf *~
	rm -rf *_Dict*
