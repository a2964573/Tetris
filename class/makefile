CXX = g++
CXXFLAGS = -Wall -g

BUILDDIR = ../build/class

OBJS =	$(BUILDDIR)/user.o \
		$(BUILDDIR)/util.o \
		$(BUILDDIR)/crypt.o \

all: user util crypt

user: user.cpp
	@if [ ! -d $(BUILDDIR) ]; then mkdir -p $(BUILDDIR); fi
	$(CXX) $(CXXFLAGS) -c user.cpp -o $(BUILDDIR)/user.o

util: util.cpp
	@if [ ! -d $(BUILDDIR) ]; then mkdir -p $(BUILDDIR); fi
	$(CXX) $(CXXFLAGS) -c util.cpp -o $(BUILDDIR)/util.o

crypt: crypt.cpp
	@if [ ! -d $(BUILDDIR) ]; then mkdir -p $(BUILDDIR); fi
	$(CXX) $(CXXFLAGS) -c crypt.cpp -o $(BUILDDIR)/crypt.o

clean:
	rm -f $(OBJS)
