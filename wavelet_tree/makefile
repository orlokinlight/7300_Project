CFLAGS = -O2 -Wall -std=c++0x

OBJS = RankedBitmap.o WaveletTree.o FmIndex.o util.o
MAINS = main

all: $(MAINS)

%.o: %.cpp
	g++ -c $< -o $@ $(CFLAGS)

main: $(OBJS) main.cpp
	g++ $+ -o $@ $(CFLAGS)


clean:
	rm -f *.o
	rm -f *.out
	rm -f $(MAINS)