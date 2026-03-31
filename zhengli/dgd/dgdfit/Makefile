### ROOT setting
#ROOTLIBS = `root-config --libs` -lMinuit -lRooStats -lRooFit -lThread -lRooFitCore -lMathCore -lMathMore
ROOTLIBS = `root-config --libs` -lRooFit -lHtml -lThread -lMinuit -lRooFitCore -lMathCore -lRooStats -lMathMore
OPTCOMP = `root-config --cflags`

### FLAGS
SPECIALFLAGS= --exceptions
LFLAGS =
RCXX = $(ROOTCFLAGS)
DBG = -g -L -O -w 

CC = g++ ${DBG} $(RCXX) $(OPTCOMP)
### Src
#Src =
Src = ../src/

### targets
all: fitDgd

LinkSrc= fitDgd.o  RooBinnedPdf.o RooEffResModel.o RooAbsEffResModel.o RooEffConvGenContext.o RooCubicSplineFun.o RooCubicSplineKnot.o RooAbsGaussModelEfficiency.o
fitDgd: $(LinkSrc) 
	$(CC) $(LinkSrc) $(ROOTLIBS) -o fitDgd

fitDgd.o: fitDgd.cpp
	$(CC) -c fitDgd.cpp -o fitDgd.o

RooBinnedPdf.o: ${Src}RooBinnedPdf.cxx ${Src}RooBinnedPdf.h 
	$(CC) -c ${Src}RooBinnedPdf.cxx -o RooBinnedPdf.o

RooEffResModel.o: ${Src}RooEffResModel.cxx ${Src}RooEffResModel.h 
	$(CC) -c ${Src}RooEffResModel.cxx -o RooEffResModel.o

RooAbsEffResModel.o: ${Src}RooAbsEffResModel.cxx ${Src}RooAbsEffResModel.h 
	$(CC) -c ${Src}RooAbsEffResModel.cxx -o RooAbsEffResModel.o

RooEffConvGenContext.o: ${Src}RooEffConvGenContext.cxx ${Src}RooEffConvGenContext.h 
	$(CC) -c ${Src}RooEffConvGenContext.cxx -o RooEffConvGenContext.o

RooCubicSplineFun.o: ${Src}RooCubicSplineFun.cxx ${Src}RooCubicSplineFun.h 
	$(CC) -c ${Src}RooCubicSplineFun.cxx -o RooCubicSplineFun.o

RooCubicSplineKnot.o: ${Src}RooCubicSplineKnot.cxx ${Src}RooCubicSplineKnot.h 
	$(CC) -c ${Src}RooCubicSplineKnot.cxx -o RooCubicSplineKnot.o

RooAbsGaussModelEfficiency.o: ${Src}RooAbsGaussModelEfficiency.cxx ${Src}RooAbsGaussModelEfficiency.h 
	$(CC) -c ${Src}RooAbsGaussModelEfficiency.cxx -o RooAbsGaussModelEfficiency.o

### clean up
clean:
	rm -rf *.o
	rm -rf *~
	rm -rf *_Dict*
	rm -rf fitDgd
clean1:
	rm -rf *.o
	rm -rf *~
	rm -rf *_Dict*
