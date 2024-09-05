CXX = g++
CXXFLAGS = -Wall -g

BUILDDIR = ../build/class

OBJS =	$(BUILDDIR)/user.o \
		$(BUILDDIR)/util.o \
		$(BUILDDIR)/environment.o \

all: user util environment

user: user.cpp
	@if [ ! -d $(BUILDDIR) ]; then mkdir -p $(BUILDDIR); fi
	$(CXX) $(CXXFLAGS) -c user.cpp -o $(BUILDDIR)/user.o

util: util.cpp
	@if [ ! -d $(BUILDDIR) ]; then mkdir -p $(BUILDDIR); fi
	$(CXX) $(CXXFLAGS) -c util.cpp -o $(BUILDDIR)/util.o

environment: environment.cpp
	@if [ ! -d $(BUILDDIR) ]; then mkdir -p $(BUILDDIR); fi
	$(CXX) $(CXXFLAGS) -c environment.cpp -o $(BUILDDIR)/environment.o

clean:
	rm -f $(OBJS)
