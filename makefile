CXX = g++
CXXFLAGS = -Wall -g

BUILDDIR = build
SUBDIRS  = class interface framework

OBJS = 	$(BUILDDIR)/Util.o \
		$(BUILDDIR)/User.o \
		$(BUILDDIR)/Environment.o \
		$(BUILDDIR)/client.o \
		$(BUILDDIR)/login.o \
		$(BUILDDIR)/main.o

TARGET = tetris.exe

all: sub main

main: main.cpp
	@if [ ! -d $(BUILDDIR) ]; then mkdir -p $(BUILDDIR); fi
	$(CXX) $(CXXFLAGS) -c main.cpp -o $(BUILDDIR)/main.o

sub:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

clean:
	rm -f $(BUILDDIR)/main.o

cleanall:
	rm -f $(BUILDDIR)/*.o

upver:
	rm -f $(TARGET)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
