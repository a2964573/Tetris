CXX = g++
CXXFLAGS = -Wall -g

BUILDDIR = ../build/class

OBJS =	$(BUILDDIR)/user.o \
		$(BUILDDIR)/util.o \

all: user util

user: user.cpp
	@if [ ! -d $(BUILDDIR) ]; then mkdir -p $(BUILDDIR); fi
	$(CXX) $(CXXFLAGS) -c user.cpp -o $(BUILDDIR)/user.o

util: util.cpp
	@if [ ! -d $(BUILDDIR) ]; then mkdir -p $(BUILDDIR); fi
	$(CXX) $(CXXFLAGS) -c util.cpp -o $(BUILDDIR)/util.o

clean:
	rm -f $(OBJS)
