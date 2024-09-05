CXX = g++
CXXFLAGS = -Wall -g

BUILDDIR = ../build/interface

OBJS = $(BUILDDIR)/client.o

all: client

client: client.cpp
	@if [ ! -d $(BUILDDIR) ]; then mkdir -p $(BUILDDIR); fi
	$(CXX) $(CXXFLAGS) -c client.cpp -o $(BUILDDIR)/client.o

clean:
	rm -f $(OBJS)
