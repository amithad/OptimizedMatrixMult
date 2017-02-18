appname := OptimizedmMatMul

CXX := g++
CXXFLAGS := -fmessage-length=0 -fopenmp -O3 -march=native -mtune=native -funroll-loops -ftree-vectorize -ftree-vectorizer-verbose=1  -ffast-math -fassociative-math

srcfiles := $(shell find . -name "*.cpp")
objects  := $(patsubst %.C, %.o, $(srcfiles))

all: $(appname)

$(appname): $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)

depend: .depend

.depend: $(srcfiles)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	rm -f $(objects)

dist-clean: clean
	rm -f *~ .depend

include .depend
