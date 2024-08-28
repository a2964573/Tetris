CXX = g++
CXXFLAGS = -Wall -g

BUILDDIR = ../build

OBJS = $(BUILDDIR)/login.o

all: $(OBJS)

$(BUILDDIR)/login.o: login.cpp
	@if [ ! -d $(BUILDDIR) ]; then mkdir -p $(BUILDDIR); fi
	$(CXX) $(CXXFLAGS) -c login.cpp -o $(BUILDDIR)/login.o

clean:
	rm -f $(OBJS)
