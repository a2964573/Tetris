CXX = g++
CXXFLAGS = -Wall -g

BUILDDIR = build
SUBDIRS  = class framework

OBJS = 	$(BUILDDIR)/Util.o \
		$(BUILDDIR)/User.o \
		$(BUILDDIR)/login.o \
		$(BUILDDIR)/main.o

TARGET = tetris.exe

all: sub main

# $(TARGET): $(OBJS)
# 	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

main: main.cpp
	@if [ ! -d $(BUILDDIR) ]; then mkdir -p $(BUILDDIR); fi
	$(CXX) $(CXXFLAGS) -c main.cpp -o $(BUILDDIR)/main.o

sub:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

clean:
	rm -f $(BUILDDIR)/*.o

upver:
	rm -f $(TARGET)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
