all: MyCopy ForkCopy PipeCopy timer
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
timer: timer.o
	g++ timer.o -o timer
timer.o:
	g++ -c timer.c
