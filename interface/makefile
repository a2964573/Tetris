CXX = g++
CXXFLAGS = -Wall -g

BUILDDIR = ../build

OBJS = $(BUILDDIR)/client.o

all: $(OBJS)

$(BUILDDIR)/client.o: client.cpp
	@if [ ! -d $(BUILDDIR) ]; then mkdir -p $(BUILDDIR); fi
	$(CXX) $(CXXFLAGS) -c client.cpp -o $(BUILDDIR)/client.o

clean:
	rm -f $(OBJS)
