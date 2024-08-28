CXX = g++
CXXFLAGS = -Wall -g

BUILDDIR = ../build

OBJS = 	$(BUILDDIR)/User.o \
		$(BUILDDIR)/Util.o

all: $(OBJS)

$(BUILDDIR)/Util.o: Util.cpp
	@if [ ! -d $(BUILDDIR) ]; then mkdir -p $(BUILDDIR); fi
	$(CXX) $(CXXFLAGS) -c Util.cpp -o $(BUILDDIR)/Util.o

$(BUILDDIR)/User.o: User.cpp
	@if [ ! -d $(BUILDDIR) ]; then mkdir -p $(BUILDDIR); fi
	$(CXX) $(CXXFLAGS) -c User.cpp -o $(BUILDDIR)/User.o

clean:
	rm -f $(OBJS)