all: MyCopy ForkCopy PipeCopy
clear:
	rm *.o
MyCopy: MyCopy.o
	g++ MyCopy.o -o MyCopy
MyCopy.o:
	g++ -c MyCopy.c
ForkCopy: ForkCopy.o
	g++ ForkCopy.o -o ForkCopy
ForkCopy.o:
	g++ -c ForkCopy.c
PipeCopy: PipeCopy.o
	g++ PipeCopy.o -o PipeCopy
PipeCopy.o:
	g++ -c PipeCopy.c
