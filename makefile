all: MyCopy ForkCopy
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
