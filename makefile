EXE = paf

OBJS_EXE = RGBAPixel.o lodepng.o PNG.o main.o twoDtree.o stats.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic 
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpthread -lm 

all : paf

$(EXE) : $(OBJS_EXE)
	$(LD) $(OBJS_EXE) $(LDFLAGS) -o $(EXE)

#object files
RGBAPixel.o : util/RGBAPixel.cpp util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) util/RGBAPixel.cpp -o $@

PNG.o : util/PNG.cpp util/PNG.h util/RGBAPixel.h util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) util/PNG.cpp -o $@

lodepng.o : util/lodepng/lodepng.cpp util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) util/lodepng/lodepng.cpp -o $@

stats.o : stats.h stats.cpp util/RGBAPixel.h util/PNG.h
	$(CXX) $(CXXFLAGS) stats.cpp -o $@

twoDtree.o : twoDtree.h twoDtree.cpp stats.h util/PNG.h util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) twoDtree.cpp -o $@

main.o : main.cpp util/PNG.h util/RGBAPixel.h twoDtree.h
	$(CXX) $(CXXFLAGS) main.cpp -o main.o

clean :
	-rm -f *.o $(EXE)